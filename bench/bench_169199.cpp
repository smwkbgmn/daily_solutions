#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <tuple>
#include <string>
#include <chrono>
#include <random>
#include <functional>

using namespace std;

// First implementation - using position encoding
int solution1(vector<string> board) {
    int r_max = board.size(), c_max = board.front().length();
    
    queue<int> q;
    unordered_set<int> record;

	int goal;
    for (auto r = 0; r < r_max; ++r) {
        for (auto c = 0; c < c_max; ++c) {
            if (board[r][c] == 'R') {
                q.push(r * 100 + c);
				record.insert(r * 100 + c);
            } else if (board[r][c] == 'G') {
				goal = r * 100 + c;
			}
        }
    }
    
	const int dirs[4] = {100, 1, -100, -1};

    auto slide = [&](int pos, int dir) -> int {
        int r = pos / 100, c = pos % 100;

        while (0 <= r && r < r_max &&
               0 <= c && c < c_max &&
               board[r][c] != 'D') {
            r += dir / 100;
            c += dir % 100;
        }
        
        int next = r * 100 + c;
        return (next != pos)? next - dir : pos;
    };
    
    int move = 0;
    while (!q.empty()) {
        for (size_t i = 0, size = q.size(); i < size; ++i) {
            int pos = q.front();
            q.pop();

            if (pos == goal) {
                return move;
            }
            
            for (auto i = 0; i < 4; ++i) {
				int next = slide(pos, dirs[i]);
                if (record.insert(next).second) {
                    q.push(next);
                }
            }
        }
        ++move;
    }
    
    return -1;
}

// Second implementation - using tuples
int solution2(vector<string> board) {
    int n = board.size();
    int m = board[0].size();

    vector<vector<bool>> visited(n, vector<bool>(m, false));
    int x, y, tx, ty;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (board[i][j] == 'R') {
                x = i;
                y = j;
            } else if (board[i][j] == 'G') {
                tx = i;
                ty = j;
            }
        }
    }

    int dx[] = {-1, 1, 0, 0}; 
    int dy[] = {0, 0, -1, 1};

    queue<tuple<int, int, int>> q; 
    q.push(make_tuple(x, y, 0));
    visited[x][y] = true;

    while (!q.empty()) {
        int x, y, cnt;
        tie(x, y, cnt) = q.front();
        q.pop();

        if (x == tx && y == ty) return cnt;

        for (int dir = 0; dir < 4; ++dir) {
            int nx = x;
            int ny = y;

            while (true) {
                int tx = nx + dx[dir];
                int ty = ny + dy[dir];

                if (tx < 0 || ty < 0 || tx >= n || ty >= m || board[tx][ty] == 'D') break;
                nx = tx;
                ny = ty;
            }

            if (!visited[nx][ny]) {
                visited[nx][ny] = true;
                q.push(make_tuple(nx, ny, cnt + 1));
            }
        }
    }

    return -1; 
}

// Generate random test case
vector<string> generateRandomBoard(int rows, int cols, int difficulty) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> obstacleProb(0, 100);
    
    vector<string> board(rows, string(cols, '.'));
    
    // Place obstacles
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (obstacleProb(gen) < difficulty) {
                board[i][j] = 'D';
            }
        }
    }
    
    // Place start position
    int startRow, startCol, goalRow, goalCol;
    do {
        startRow = gen() % rows;
        startCol = gen() % cols;
    } while (board[startRow][startCol] == 'D');
    board[startRow][startCol] = 'R';
    
    // Place goal position
    do {
        goalRow = gen() % rows;
        goalCol = gen() % cols;
    } while (board[goalRow][goalCol] == 'D' || (goalRow == startRow && goalCol == startCol));
    board[goalRow][goalCol] = 'G';
    
    return board;
}

void runBenchmark(const vector<vector<string>>& testCases) {
    cout << "Benchmark Results:\n";
    cout << "==================\n";
    
    double totalTime1 = 0.0;
    double totalTime2 = 0.0;
    
    for (size_t i = 0; i < testCases.size(); i++) {
        cout << "Test Case " << i+1 << " (" << testCases[i].size() << "x" << testCases[i][0].size() << "):\n";
        
        // Time solution1
        auto start1 = chrono::high_resolution_clock::now();
        int result1 = solution1(testCases[i]);
        auto end1 = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> time1 = end1 - start1;
        totalTime1 += time1.count();
        
        // Time solution2
        auto start2 = chrono::high_resolution_clock::now();
        int result2 = solution2(testCases[i]);
        auto end2 = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> time2 = end2 - start2;
        totalTime2 += time2.count();
        
        cout << "  Solution1 time: " << time1.count() << " ms, Result: " << result1 << "\n";
        cout << "  Solution2 time: " << time2.count() << " ms, Result: " << result2 << "\n";
        
        if (result1 != result2) {
            cout << "  WARNING: Different results!\n";
        }
        
        double speedup = time1.count() / time2.count();
        cout << "  Speedup (Solution2/Solution1): " << speedup << "x\n\n";
    }
    
    cout << "Overall Results:\n";
    cout << "  Solution1 total time: " << totalTime1 << " ms\n";
    cout << "  Solution2 total time: " << totalTime2 << " ms\n";
    cout << "  Overall speedup: " << totalTime1 / totalTime2 << "x\n";
}

int main() {
    // Test cases of increasing size and complexity
    vector<vector<string>> testCases;
    
    // Small test case
    testCases.push_back({
        "RD..",
        "....",
        "....",
        "..G."
    });
    
    // Medium test case
    vector<string> medium = generateRandomBoard(10, 10, 20);
    testCases.push_back(medium);
    
    // Large test case
    vector<string> large = generateRandomBoard(20, 20, 25);
    testCases.push_back(large);
    
    // Very large test case
    vector<string> veryLarge = generateRandomBoard(50, 50, 30);
    testCases.push_back(veryLarge);
    
    // Run the benchmark
    runBenchmark(testCases);
    
    return 0;
}