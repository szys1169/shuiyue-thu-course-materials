#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Beam {
    int start;
    int finish;
    int energy;
};

int main() {
    int n;
    cin >> n;
    vector<Beam> beams(n);
    for (Beam& beam : beams) {
        cin >> beam.start >> beam.finish >> beam.energy;
    }

    sort(beams.begin(), beams.end(), [](const Beam& left, const Beam& right) {
        return left.energy > right.energy;
    });

    vector<Beam> selected;
    long long answer = 0;
    for (const Beam& candidate : beams) {
        bool conflicts = false;
        for (const Beam& chosen : selected) {
            if (!(candidate.finish <= chosen.start
                || chosen.finish <= candidate.start)) {
                conflicts = true;
                break;
            }
        }
        if (!conflicts) {
            selected.push_back(candidate);
            answer += candidate.energy;
        }
    }

    cout << answer << '\n';
    return 0;
}
