#!/bin/bash

# Couleurs
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
MAGENTA='\033[0;35m'
CYAN='\033[0;36m'
NC='\033[0m' # No Color

# Compteurs
PASSED=0
FAILED=0
TOTAL=0

# Fichiers temporaires
PIPEX_OUT="pipex_out.txt"
SHELL_OUT="shell_out.txt"
TEST_INPUT="test_input.txt"

# Fonction de nettoyage
cleanup() {
    rm -f $PIPEX_OUT $SHELL_OUT $TEST_INPUT
    rm -f empty_file big_file special_file numbers
    rm -f noperm_in noperm_out
    rm -f test_*.txt
}

# Nettoyage au début et à la fin
trap cleanup EXIT
cleanup

# Vérifier que pipex existe
if [ ! -f "./pipex" ]; then
    echo -e "${RED}Erreur: ./pipex n'existe pas${NC}"
    echo "Compilez d'abord votre projet avec 'make'"
    exit 1
fi

# Fonction pour afficher un header
print_header() {
    echo ""
    echo -e "${CYAN}========================================${NC}"
    echo -e "${CYAN}  $1${NC}"
    echo -e "${CYAN}========================================${NC}"
    echo ""
}

# Fonction pour tester avec comparaison shell
test_with_shell() {
    local test_name="$1"
    local input_file="$2"
    local cmd1="$3"
    local cmd2="$4"
    
    ((TOTAL++))
    echo -n "Test $TOTAL: $test_name ... "
    
    # Exécuter pipex
    ./pipex "$input_file" "$cmd1" "$cmd2" $PIPEX_OUT 2>/dev/null
    pipex_ret=$?
    
    # Exécuter shell équivalent
    eval "< \"$input_file\" $cmd1 | $cmd2 > $SHELL_OUT 2>/dev/null"
    shell_ret=$?
    
    # Comparer les sorties
    if diff -q $PIPEX_OUT $SHELL_OUT >/dev/null 2>&1; then
        echo -e "${GREEN}✓ PASSED${NC}"
        ((PASSED++))
        return 0
    else
        echo -e "${RED}✗ FAILED${NC}"
        echo -e "  ${YELLOW}Expected (shell):${NC}"
        head -n 3 $SHELL_OUT | sed 's/^/    /'
        echo -e "  ${YELLOW}Got (pipex):${NC}"
        head -n 3 $PIPEX_OUT | sed 's/^/    /'
        ((FAILED++))
        return 1
    fi
}

# Fonction pour tester le code de retour
test_exit_code() {
    local test_name="$1"
    local expected_code="$2"
    shift 2
    
    ((TOTAL++))
    echo -n "Test $TOTAL: $test_name ... "
    
    # Exécuter la commande
    "$@" >/dev/null 2>&1
    actual_code=$?
    
    if [ $actual_code -eq $expected_code ]; then
        echo -e "${GREEN}✓ PASSED${NC} (exit: $actual_code)"
        ((PASSED++))
        return 0
    else
        echo -e "${RED}✗ FAILED${NC} (expected: $expected_code, got: $actual_code)"
        ((FAILED++))
        return 1
    fi
}

# Fonction pour tester qu'un fichier est créé
test_file_created() {
    local test_name="$1"
    local output_file="$2"
    shift 2
    
    ((TOTAL++))
    echo -n "Test $TOTAL: $test_name ... "
    
    rm -f "$output_file"
    "$@" >/dev/null 2>&1
    
    if [ -f "$output_file" ]; then
        echo -e "${GREEN}✓ PASSED${NC}"
        ((PASSED++))
        rm -f "$output_file"
        return 0
    else
        echo -e "${RED}✗ FAILED${NC} (file not created)"
        ((FAILED++))
        return 1
    fi
}

# Créer les fichiers de test
create_test_files() {
    echo -e "hello world\nbonjour monde\nhello universe\ntest line\nhello\nworld" > $TEST_INPUT
    echo -e "line1\nline2\nline3\nline4\nline5" > test_simple.txt
    touch empty_file
    seq 1 10000 > big_file
    echo -e "hello\nworld\n\$test\n'quote'\n\"double\"" > special_file
    seq 1 100 > numbers
}

# ============================================
# DÉBUT DES TESTS
# ============================================

clear
echo -e "${MAGENTA}"
echo "╔════════════════════════════════════════╗"
echo "║                                        ║"
echo "║         PIPEX TEST SUITE               ║"
echo "║                                        ║"
echo "╚════════════════════════════════════════╝"
echo -e "${NC}"

create_test_files

# ============================================
print_header "1. TESTS DE BASE"
# ============================================

test_with_shell "cat | wc -l" "$TEST_INPUT" "cat" "wc -l"
test_with_shell "grep hello | wc -l" "$TEST_INPUT" "grep hello" "wc -l"
test_with_shell "cat | cat" "$TEST_INPUT" "cat" "cat"
test_with_shell "grep world | cat" "$TEST_INPUT" "grep world" "cat"
test_with_shell "cat -e | head -n 3" "$TEST_INPUT" "cat -e" "head -n 3"

# ============================================
print_header "2. TESTS AVEC ARGUMENTS MULTIPLES"
# ============================================

test_with_shell "cat -e | grep $" "$TEST_INPUT" "cat -e" "grep \\\$"
test_with_shell "head -n 3 | tail -n 1" "numbers" "head -n 3" "tail -n 1"
test_with_shell "grep -i HELLO | wc -l" "$TEST_INPUT" "grep -i HELLO" "wc -l"
test_with_shell "cat -n | head -n 2" "$TEST_INPUT" "cat -n" "head -n 2"

# ============================================
print_header "3. TESTS AVEC FICHIERS SPÉCIAUX"
# ============================================

test_with_shell "empty file: cat | wc -l" "empty_file" "cat" "wc -l"
test_with_shell "big file: grep 5 | wc -l" "big_file" "grep 5" "wc -l"
test_with_shell "special chars: cat | grep test" "special_file" "cat" "grep test"

# ============================================
print_header "4. TESTS D'ERREURS - FICHIERS"
# ============================================

# Fichier d'entrée inexistant
((TOTAL++))
echo -n "Test $TOTAL: fichier d'entrée inexistant ... "
./pipex fichier_qui_nexiste_pas "cat" "wc -l" $PIPEX_OUT 2>/dev/null
if [ -f $PIPEX_OUT ]; then
    echo -e "${GREEN}✓ PASSED${NC} (outfile créé malgré erreur)"
    ((PASSED++))
else
    echo -e "${RED}✗ FAILED${NC} (outfile devrait être créé)"
    ((FAILED++))
fi

# ============================================
print_header "5. TESTS D'ERREURS - COMMANDES"
# ============================================

test_exit_code "commande invalide (première)" 127 ./pipex "$TEST_INPUT" "commandeinexistante" "wc -l" $PIPEX_OUT
test_exit_code "commande invalide (deuxième)" 127 ./pipex "$TEST_INPUT" "cat" "commandeinexistante" $PIPEX_OUT
test_exit_code "deux commandes invalides" 127 ./pipex "$TEST_INPUT" "cmd1invalide" "cmd2invalide" $PIPEX_OUT

# ============================================
print_header "6. TESTS D'ARGUMENTS"
# ============================================

test_exit_code "pas assez d'arguments (3 args)" 1 ./pipex "$TEST_INPUT" "cat" $PIPEX_OUT
test_exit_code "pas assez d'arguments (2 args)" 1 ./pipex "$TEST_INPUT" "cat"
test_exit_code "pas assez d'arguments (1 arg)" 1 ./pipex "$TEST_INPUT"
test_exit_code "aucun argument" 1 ./pipex

# ============================================
print_header "7. TESTS AVEC CHEMINS ABSOLUS/RELATIFS"
# ============================================

test_with_shell "chemin absolu /bin/cat" "$TEST_INPUT" "/bin/cat" "wc -l"
test_with_shell "chemin absolu /usr/bin/wc" "$TEST_INPUT" "cat" "/usr/bin/wc -l"

# ============================================
print_header "8. TESTS DE PERMISSIONS"
# ============================================

# Créer fichiers avec permissions
touch noperm_in
chmod 000 noperm_in

((TOTAL++))
echo -n "Test $TOTAL: fichier d'entrée non lisible ... "
./pipex noperm_in "cat" "wc -l" $PIPEX_OUT 2>/dev/null
ret=$?
if [ $ret -ne 0 ]; then
    echo -e "${GREEN}✓ PASSED${NC} (erreur détectée)"
    ((PASSED++))
else
    echo -e "${RED}✗ FAILED${NC} (devrait échouer)"
    ((FAILED++))
fi

chmod 644 noperm_in
rm -f noperm_in

# ============================================
print_header "9. TESTS AVANCÉS"
# ============================================

test_with_shell "awk print | cat" "$TEST_INPUT" "awk '{print \$1}'" "cat"
test_with_shell "sed substitution | cat" "$TEST_INPUT" "sed 's/hello/HELLO/g'" "cat"
test_with_shell "sort | uniq" "$TEST_INPUT" "sort" "uniq"
test_with_shell "head | tail" "numbers" "head -n 50" "tail -n 10"

# ============================================
print_header "10. TESTS DE CRÉATION DE FICHIER"
# ============================================

test_file_created "création fichier sortie" "new_output.txt" ./pipex "$TEST_INPUT" "cat" "wc -l" "new_output.txt"

# Test d'écrasement de fichier
echo "old content" > existing.txt
((TOTAL++))
echo -n "Test $TOTAL: écrasement fichier existant ... "
./pipex "$TEST_INPUT" "cat" "head -n 1" existing.txt 2>/dev/null
if [ -f existing.txt ] && ! grep -q "old content" existing.txt; then
    echo -e "${GREEN}✓ PASSED${NC}"
    ((PASSED++))
else
    echo -e "${RED}✗ FAILED${NC} (fichier devrait être écrasé)"
    ((FAILED++))
fi
rm -f existing.txt

# ============================================
print_header "11. TESTS DE STRESS"
# ============================================

((TOTAL++))
echo -n "Test $TOTAL: exécution multiple (10x) ... "
success=0
for i in {1..10}; do
    ./pipex "$TEST_INPUT" "cat" "wc -l" $PIPEX_OUT 2>/dev/null
    if [ $? -eq 0 ]; then
        ((success++))
    fi
done
if [ $success -eq 10 ]; then
    echo -e "${GREEN}✓ PASSED${NC} (10/10 réussies)"
    ((PASSED++))
else
    echo -e "${RED}✗ FAILED${NC} ($success/10 réussies)"
    ((FAILED++))
fi

# ============================================
print_header "12. TEST BONUS - VALGRIND (si disponible)"
# ============================================

if command -v valgrind &> /dev/null; then
    ((TOTAL++))
    echo -n "Test $TOTAL: test de fuites mémoire ... "
    valgrind --leak-check=full --error-exitcode=42 ./pipex "$TEST_INPUT" "cat" "wc -l" $PIPEX_OUT > /dev/null 2>&1
    if [ $? -ne 42 ]; then
        echo -e "${GREEN}✓ PASSED${NC} (pas de fuites)"
        ((PASSED++))
    else
        echo -e "${RED}✗ FAILED${NC} (fuites détectées)"
        ((FAILED++))
    fi
else
    echo -e "${YELLOW}Valgrind non installé - test ignoré${NC}"
fi

# ============================================
# RÉSUMÉ FINAL
# ============================================

echo ""
echo -e "${CYAN}========================================${NC}"
echo -e "${CYAN}           RÉSULTATS FINAUX${NC}"
echo -e "${CYAN}========================================${NC}"
echo ""

percentage=$((PASSED * 100 / TOTAL))

echo -e "Total de tests : ${BLUE}$TOTAL${NC}"
echo -e "Réussis        : ${GREEN}$PASSED${NC}"
echo -e "Échoués        : ${RED}$FAILED${NC}"
echo -e "Pourcentage    : ${MAGENTA}$percentage%${NC}"
echo ""

if [ $FAILED -eq 0 ]; then
    echo -e "${GREEN}╔════════════════════════════════════════╗${NC}"
    echo -e "${GREEN}║                                        ║${NC}"
    echo -e "${GREEN}║     🎉  TOUS LES TESTS RÉUSSIS  🎉     ║${NC}"
    echo -e "${GREEN}║                                        ║${NC}"
    echo -e "${GREEN}╚════════════════════════════════════════╝${NC}"
    exit 0
elif [ $percentage -ge 80 ]; then
    echo -e "${YELLOW}╔════════════════════════════════════════╗${NC}"
    echo -e "${YELLOW}║      Bon travail ! Quelques bugs      ║${NC}"
    echo -e "${YELLOW}╚════════════════════════════════════════╝${NC}"
    exit 1
else
    echo -e "${RED}╔════════════════════════════════════════╗${NC}"
    echo -e "${RED}║     Plusieurs tests ont échoué        ║${NC}"
    echo -e "${RED}╚════════════════════════════════════════╝${NC}"
    exit 1
fi