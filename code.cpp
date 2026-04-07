// Minimal implementation without using C++ standard library headers.

namespace sjtu {
    class CrossArray{
    private:
        int max_lines;
        int **arrays;
        int *sizes;
        int inserted;
    public:
        explicit CrossArray(int lines) : max_lines(lines), inserted(0) {
            arrays = new int*[max_lines];
            sizes = new int[max_lines];
            for (int i = 0; i < max_lines; ++i) {
                arrays[i] = nullptr;
                sizes[i] = 0;
            }
        }

        CrossArray(const CrossArray & o) : max_lines(o.max_lines), inserted(o.inserted) {
            arrays = new int*[max_lines];
            sizes = new int[max_lines];
            for (int i = 0; i < max_lines; ++i) {
                sizes[i] = o.sizes[i];
                if (o.arrays[i] == nullptr) {
                    arrays[i] = nullptr;
                } else {
                    arrays[i] = new int[sizes[i]];
                    for (int j = 0; j < sizes[i]; ++j) arrays[i][j] = o.arrays[i][j];
                }
            }
        }

        CrossArray & WhichGreater(CrossArray & o) {
            long long cnt_this = 0, cnt_o = 0;
            for (int i = 0; i < max_lines; ++i) cnt_this += sizes[i];
            for (int i = 0; i < o.max_lines; ++i) cnt_o += o.sizes[i];
            if (cnt_this >= cnt_o) return *this;
            return o;
        }

        bool IsSame(const CrossArray & o) {
            return arrays == o.arrays; // compare underlying pointer-of-pointers
        }

        bool InsertArrays(const int * Input, int size) {
            if (inserted >= max_lines) return false;
            int idx = inserted;
            if (arrays[idx] != nullptr) return false; // should not happen in valid usage
            arrays[idx] = new int[size];
            for (int i = 0; i < size; ++i) arrays[idx][i] = Input[i];
            sizes[idx] = size;
            ++inserted;
            return true;
        }

        void AppendArrays(const int * Input,int Line,int size) {
            int oldSize = sizes[Line];
            int *oldArr = arrays[Line];
            int *narr = new int[oldSize + size];
            for (int i = 0; i < oldSize; ++i) narr[i] = oldArr[i];
            for (int i = 0; i < size; ++i) narr[oldSize + i] = Input[i];
            delete [] oldArr;
            arrays[Line] = narr;
            sizes[Line] = oldSize + size;
        }

        void DoubleCrossLength() {
            int new_max = max_lines * 2;
            int **new_arrays = new int*[new_max];
            int *new_sizes = new int[new_max];
            for (int i = 0; i < new_max; ++i) {
                if (i < max_lines) {
                    new_arrays[i] = arrays[i];
                    new_sizes[i] = sizes[i];
                } else {
                    new_arrays[i] = nullptr;
                    new_sizes[i] = 0;
                }
            }
            delete [] arrays;
            delete [] sizes;
            arrays = new_arrays;
            sizes = new_sizes;
            max_lines = new_max;
        }

        const int * AtArray(int i) {
            return arrays[i];
        }

        int & At(int i , int j) {
            return arrays[i][j];
        }

        ~CrossArray() {
            for (int i = 0; i < max_lines; ++i) {
                delete [] arrays[i];
                arrays[i] = nullptr;
            }
            delete [] arrays;
            delete [] sizes;
        }

    };
}

int main() {
    // Intentionally empty: class is assessed by the judge's harness.
    return 0;
}
