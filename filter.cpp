#include <string>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class FilterSequence
{
    public:
        FilterSequence(char** filter) {
            this->filterParams = filter;
        }

        bool filter(int size, int* intSequence) {
            switch (this->filterCode(this->filterParams[0])) {
                // key: -s
                case 11635: {
                    return this->sequenceOfN(size, atoi(this->filterParams[1]), intSequence);
                }
            }

            return false;
        }
    private:
        char** filterParams;

        int filterCode(char* filterName) {
            int result = 0;

            for (int i = 0; i < strlen(filterName); ++i) {
                result <<= 8;
                result += (int) filterName[i];
            }

            return result;
        }

        bool sequenceOfN(int size, int count, int* sequence) {
            bool test = false;
            bool subTest = false;

            for (int i = 0; i < size - (count - 1); ++i) {
                subTest = true;

                for (int j = 0; j < count; ++j) {
                    if (sequence[i] - sequence[i + j] != -j) {
                        subTest = false;
                        break;
                    }
                }

                if (subTest) {
                    test = true;
                    break;
                }
            }

            return test;
        }
};

int main(int argc, char* argv[])
{
    if (argc > 1) {
        // ключи для фильтра
        char** filter = (char**) malloc((argc - 1) * sizeof(char*));
        memcpy(filter, argv + 1, (argc - 1) * sizeof(char*));

        // создаем фильтр, передаем параметры
        FilterSequence filterSeq(filter);

        // анализируем последовательности
        char* input = (char*) malloc(1024 * sizeof(char));

        while (fgets(input, 1024, stdin) != 0) {
            vector<int> seq;

            char* parts = strtok(input, " ");

            while (parts != NULL) {
                if ((int) *parts != 0x0A) {
                    seq.push_back(atoi(parts));
                }

                parts = strtok(NULL, " ");
            }

            if (seq.size() > 0) {
                int* data = (int*) malloc(seq.size() * sizeof(int));

                for (int i = 0; i < seq.size(); ++i) {
                    data[i] = seq[i];
                }

                if (filterSeq.filter(seq.size(), data)) {
                    for (int i = 0; i < seq.size(); ++i) {
                        cout << data[i];

                        if (i < seq.size() - 1) {
                            cout << " ";
                        }
                    }

                    cout << "\n";
                }
            }
        }
    } else {
        cout << "Not found";
    }

    return 0;
}
