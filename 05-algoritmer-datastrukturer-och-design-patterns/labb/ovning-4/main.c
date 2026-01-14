#include "list.h"
#include "stack.h"
#include "queue.h"
#include "set.h"

#include <stdio.h>
#include <stdlib.h>

// ------------------------------------------------------------
// Enkel "test-runner": PASS/FAIL utan att avbryta direkt
// ------------------------------------------------------------
static int g_pass = 0;
static int g_fail = 0;

static void check(int cond, const char* msg) {
    if (cond) {
        printf("[PASS] %s\n", msg);
        ++g_pass;
    }
    else {
        printf("[FAIL] %s\n", msg);
        ++g_fail;
    }
}

static void section(const char* title) {
    printf("\n=== %s ===\n", title);
}

// ------------------------------------------------------------
// Hjälpfunktioner för forEach / forEachCtx
// ------------------------------------------------------------
static void print_elem(Data x) {
    printf("%d ", x);
}

struct SumCtx {
    int sum;
};

static void sum_cb(Data x, void* ctx) {
    struct SumCtx* c = (struct SumCtx*)(ctx);
    c->sum += x;
}

int main() {
    puts("ADT-övning: snäll testkörning (PASS/FAIL)\n");

    // ------------------------------------------------------------
    // 1) List grundtest
    // ------------------------------------------------------------
    section("1) List grundtest");

    List l = createEmptyList();

    check(isEmpty(l), "List: ny lista ska vara tom");

    check(addFirst(&l, 2) == 1, "List: addFirst(2) ska lyckas");
    check(addFirst(&l, 1) == 1, "List: addFirst(1) ska lyckas");
    check(addLast(&l, 3) == 1, "List: addLast(3) ska lyckas");

    fputs("List l = ", stdout);

    printList(l, stdout);

    check(lengthOfList(l) == 3, "List: lengthOfList() ska vara 3");
    check(!isEmpty(l), "List: lista ska inte vara tom efter inserts");
    check(isInList(l, 2) == 1, "List: isInList(2) ska vara true");
    check(isInList(l, 99) == 0, "List: isInList(99) ska vara false");

    // getFirstElement / getLastElement har precondition: listan f�r inte vara tom
    if (!isEmpty(l)) {
        check(getFirstElement(l) == 1, "List: getFirstElement() ska vara 1");
        check(getLastElement(l) == 3, "List: getLastElement() ska vara 3");
    }
    else {
        check(0, "List: kan inte testa getFirst/getLast på tom lista");
    }

    // fputs("List forEach: ", stdout);
    // forEach(print_elem);
    // puts("");

    // SumCtx sc{ 0 };
    // l.forEachCtx(sum_cb, &sc);
    // check(sc.sum == 6, "List: forEachCtx summering ska bli 6 (1+2+3)");

    // // ------------------------------------------------------------
    // // 2) Stack test
    // // ------------------------------------------------------------
    // section("2) Stack � test");

    // Stack st;

    // // Om Stack::empty/size �r TODO och assertar, kommer programmet stoppa h�r.
    // // N�r de �r implementerade, k�r dessa tester:
    // check(st.empty(), "Stack: ny stack ska vara tom");
    // check(st.size() == 0, "Stack: size() ska vara 0 fr�n start");

    // st.push(10);
    // st.push(20);
    // st.push(30);

    // st.print(stdout);

    // check(!st.empty(), "Stack: ska inte vara tom efter push");
    // check(st.size() == 3, "Stack: size() ska vara 3 efter 3 push");

    // // peek/pop har precondition: ej tom
    // if (!st.empty()) {
    //     check(st.peek() == 30, "Stack: peek() ska ge 30");
    //     check(st.pop() == 30, "Stack: pop() ska ge 30");
    //     check(st.peek() == 20, "Stack: peek() ska ge 20 efter pop");
    //     check(st.size() == 2, "Stack: size() ska vara 2 efter pop");
    // }
    // else {
    //     check(false, "Stack: kan inte testa peek/pop p� tom stack");
    // }

    // st.clear();
    // check(st.empty(), "Stack: clear() ska g�ra stacken tom");

    // // ------------------------------------------------------------
    // // 3) Queue test
    // // ------------------------------------------------------------
    // section("3) Queue � test");

    // Queue q;

    // check(q.empty(), "Queue: ny queue ska vara tom");
    // check(q.size() == 0, "Queue: size() ska vara 0 från start");

    // q.enqueue(7);
    // q.enqueue(8);
    // q.enqueue(9);

    // q.print(stdout);

    // check(!q.empty(), "Queue: ska inte vara tom efter enqueue");
    // check(q.size() == 3, "Queue: size() ska vara 3 efter 3 enqueue");

    // if (!q.empty()) {
    //     check(q.peek() == 7, "Queue: peek() ska ge 7");
    //     check(q.dequeue() == 7, "Queue: dequeue() ska ge 7");
    //     check(q.peek() == 8, "Queue: peek() ska ge 8 efter dequeue");
    //     check(q.size() == 2, "Queue: size() ska vara 2 efter dequeue");
    // }
    // else {
    //     check(false, "Queue: kan inte testa peek/dequeue på tom queue");
    // }

    // q.clear();
    // check(q.empty(), "Queue: clear() ska göra kön tom");

    // // ------------------------------------------------------------
    // // 4) Set grundtest
    // // ------------------------------------------------------------
    // section("4) Set � grundtest");

    // Set a;
    // check(a.empty(), "Set: ny mängd ska vara tom");
    // check(a.size() == 0, "Set: size() ska vara 0 från start");

    // check(a.add(1) == true, "Set: add(1) ska returnera true");
    // check(a.add(2) == true, "Set: add(2) ska returnera true");
    // check(a.add(2) == false, "Set: add(2) igen ska returnera false (dubblett)");
    // check(a.add(3) == true, "Set: add(3) ska returnera true");

    // fputs("Set a = ", stdout);
    // a.print(stdout);

    // check(a.contains(1) == true, "Set: contains(1) ska vara true");
    // check(a.contains(99) == false, "Set: contains(99) ska vara false");
    // check(a.size() == 3, "Set: size() ska vara 3 (1,2,3)");

    // check(a.remove(2) == true, "Set: remove(2) ska returnera true");
    // check(a.remove(2) == false, "Set: remove(2) igen ska returnera false");
    // check(a.size() == 2, "Set: size() ska vara 2 efter remove(2)");

    // fputs("Set a efter remove(2) = ", stdout);
    // a.print(stdout);

    // // ------------------------------------------------------------
    // // 5) Set-operationer
    // // ------------------------------------------------------------
    // section("5) Set-operationer");

    // Set b;
    // b.add(3);
    // b.add(4);
    // b.add(5);

    // std::fputs("Set b = ", stdout);
    // b.print(stdout);

    // // Om set_union/snitt/diff är TODO och assertar, kommer programmet stoppa här.
    // Set u = Set::set_union(a, b);
    // Set i = Set::set_intersection(a, b);
    // Set d = Set::set_difference(a, b);

    // std::fputs("a union b        = ", stdout);
    // u.print(stdout);

    // std::fputs("a intersection b = ", stdout);
    // i.print(stdout);

    // std::fputs("a difference b   = ", stdout);
    // d.print(stdout);

    // // Grundkontroller (a bör nu innehålla {1,3})
    // check(u.contains(1), "Union: ska innehålla 1");
    // check(u.contains(3), "Union: ska innehålla 3");
    // check(u.contains(4), "Union: ska innehålla 4");
    // check(u.contains(5), "Union: ska innehålla 5");

    // check(i.contains(3), "Intersection: ska innehålla 3");
    // check(!i.contains(1), "Intersection: ska inte innehålla 1");
    // check(!i.contains(4), "Intersection: ska inte innehålla 4");

    // check(d.contains(1), "Difference: ska innehålla 1");
    // check(!d.contains(3), "Difference: ska inte innehålla 3 (finns i b)");

    // // ------------------------------------------------------------
    // // Summering
    // // ------------------------------------------------------------
    // section("Summering");
    // printf("PASS: %d\n", g_pass);
    // printf("FAIL: %d\n", g_fail);

    // // Exit code kan vara praktiskt i CI / automatiska tester:
    // // 0 = allt OK, 1 = minst ett fail
    // return (g_fail == 0) ? 0 : 1;
}