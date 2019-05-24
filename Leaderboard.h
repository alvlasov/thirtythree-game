#ifndef LEADERBOARD_H_INCLUDED
#define LEADERBOARD_H_INCLUDED

#include <vector>

namespace thirtythree {

class Leaderboard {
public:
    struct Entry {
        Entry(const std::vector &nname, int nscore)
            : name (nname), score (nscore) {}
        std::vector name;
        int score;
    };

    void AddEntry(const std::vector &name, int score) {
        entries_.emplace_back(name, score);
    }



private:
    std::vector<Entry> entries_;

};

}


#endif // LEADERBOARD_H_INCLUDED
