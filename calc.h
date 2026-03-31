#pragma once

#include <any>
#include <cmath>
#include "visitor.h"

struct calculator : visitor {
    std::any visit_num(num_node *n) override {
        return n->number;
    }

    std::any visit_add(add_node *n) override {
        auto l = visit(n->lnode);
        auto r = visit(n->rnode);
        // Preserve type if both sides share it; otherwise promote to double
        if (auto lp = std::any_cast<long long>(&l)) {
            if (auto rp = std::any_cast<long long>(&r)) {
                return std::any(static_cast<long long>(*lp + *rp));
            }
        }
        double lv = value_as_double(l);
        double rv = value_as_double(r);
        return std::any(lv + rv);
    }

    std::any visit_sub(sub_node *n) override {
        auto l = visit(n->lnode);
        auto r = visit(n->rnode);
        if (auto lp = std::any_cast<long long>(&l)) {
            if (auto rp = std::any_cast<long long>(&r)) {
                return std::any(static_cast<long long>(*lp - *rp));
            }
        }
        double lv = value_as_double(l);
        double rv = value_as_double(r);
        return std::any(lv - rv);
    }

    std::any visit_mul(mul_node *n) override {
        auto l = visit(n->lnode);
        auto r = visit(n->rnode);
        if (auto lp = std::any_cast<long long>(&l)) {
            if (auto rp = std::any_cast<long long>(&r)) {
                return std::any(static_cast<long long>(*lp * *rp));
            }
        }
        double lv = value_as_double(l);
        double rv = value_as_double(r);
        return std::any(lv * rv);
    }

    std::any visit_div(div_node *n) override {
        auto l = visit(n->lnode);
        auto r = visit(n->rnode);
        // Division follows C/C++ semantics: integer division if both ints; otherwise double
        if (auto lp = std::any_cast<long long>(&l)) {
            if (auto rp = std::any_cast<long long>(&r)) {
                // Guard against division by zero; let it throw or undefined? We'll mirror C++ behavior
                return std::any(static_cast<long long>(*lp / *rp));
            }
        }
        double lv = value_as_double(l);
        double rv = value_as_double(r);
        return std::any(lv / rv);
    }

    ~calculator() override = default;

private:
    static double value_as_double(const std::any &v) {
        if (auto p = std::any_cast<double>(&v)) return *p;
        if (auto p2 = std::any_cast<long long>(&v)) return static_cast<double>(*p2);
        // Fallback: treat missing as 0.0
        return 0.0;
    }
};

