//
// Created by iznets on 9/20/25.
//

#ifndef PROJECT_2025_GRUPPA_TRANSACTION_H
#define PROJECT_2025_GRUPPA_TRANSACTION_H

struct Transaction {
    int         order_id;
    double      amount;
    std::string timestamp_iso;  // "2025-09-20T15:30:00"
    bool        success;
    std::string note;

    Transaction(int id, double amt, const std::string& ts, bool ok, const std::string& n = {})
        : order_id(id), amount(amt), timestamp_iso(ts), success(ok), note(n) {}
};
#endif //PROJECT_2025_GRUPPA_TRANSACTION_H