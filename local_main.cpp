#include <iostream>
#include "calc.h"

// Simple local harness to sanity-check compilation
int main() {
    // Build (1 + 2) * (10 - 3) / 7 = 3 * 7 / 7 = 3
    num_node *n1 = new num_node; n1->number = (long long)1;
    num_node *n2 = new num_node; n2->number = (long long)2;
    add_node *add = new add_node; add->lnode = n1; add->rnode = n2;

    num_node *n10 = new num_node; n10->number = (long long)10;
    num_node *n3  = new num_node; n3->number  = (long long)3;
    sub_node *sub = new sub_node; sub->lnode = n10; sub->rnode = n3;

    mul_node *mul = new mul_node; mul->lnode = add; mul->rnode = sub;

    num_node *n7  = new num_node; n7->number  = (long long)7;
    div_node *div = new div_node; div->lnode = mul; div->rnode = n7;

    calculator calc;
    auto res = calc.visit(div);
    if (auto p = std::any_cast<long long>(&res)) {
        std::cout << *p << "\n";
    } else if (auto q = std::any_cast<double>(&res)) {
        std::cout << *q << "\n";
    } else {
        std::cout << "type error\n";
    }
    return 0;
}

