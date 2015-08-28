#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef priority_queue<int, vector<int>> numbers_queue;

numbers_queue* build_queue(int N)
{
    numbers_queue* q = new numbers_queue();
    int number;
    while (N--) {
        scanf("%d", &number);
        q->push(number);
    }
    return q;
}

int pairs(numbers_queue* q, int N, int K)
{
    int index = 0, left = 0, count = 0;
    vector<int> numbers(N);
    while (!q->empty()) {
        numbers[index] = q->top();
        q->pop();
        while (left < index && numbers[left] > numbers[index] + K) {
            left++;
        }
        if (numbers[left] == numbers[index] + K) {
            count++;
        }
        index++;
    }
    return count;
}

int main()
{
    int N, K;
    scanf("%d%d", &N, &K);
    numbers_queue* q = build_queue(N);
    printf("%d\n", pairs(q, N, K));
    delete q;
    return 0;
}
