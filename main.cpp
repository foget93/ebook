#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <iomanip>

class BookManager {
public:
    BookManager()
        : readers_on_page_(1001, 0)
    {}; // max - 1000 str

    void Read(int user_id, int page_num) {
        int cur_pages = 0;
        if (readers_.count(user_id) > 0) {
            cur_pages = readers_.at(user_id);
        }

        for (int i = cur_pages + 1; i <= page_num; ++i) {
            ++readers_on_page_[i];
        }

        readers_[user_id] = page_num;
    }

    double ComputeCheer(int user_id) {
        if (readers_.count(user_id) == 0) {
            return 0;
        }
        else if (readers_.size() == 1) {
            return 1;
        }
        else {
            int num_pages = readers_.at(user_id);
            double less_then_user_num =  readers_on_page_.at(1) - readers_on_page_.at(num_pages);

            return (less_then_user_num / (readers_.size() - 1));
        }
    }

private:
    //  Value =  будет храниться номер страницы,
    //  Key = до которой дочитал пользователь id, равным n.
    std::unordered_map<int, int> readers_;
    //По каждому индексу m будет храниться количество пользователей, дочитавших как минимум до страницы m.
    std::vector<int> readers_on_page_ ;
};

// фун-ция обработчик запросов
void ProcessRequests(std::istream& in, std::ostream& out, BookManager& book_cheker) {
    using namespace std::literals;

    int request_count {0};
    int user_id {0};
    std::string request_type;
    int page_num {0};

    in >> request_count;
    for (int request_id = 0; request_id < request_count; ++request_id) {
        in >> request_type;
        in >> user_id;
        if (request_type == "READ"s) {
            in >> page_num;
            book_cheker.Read(user_id, page_num);
        }
        else if (request_type == "CHEER"s){
            double res = book_cheker.ComputeCheer(user_id);
            out << std::setprecision(6) << res << std::endl;
        }
    }
}

/*void AddToIntsRef(int& dst1, int& dst2, const int& val) {
    dst1 += val;
    dst2 += val;
}

void AddToIntsPtr(int* dst1, int* dst2, const int* val) {
    *dst1 += *val;
    *dst2 += *val;
}

void AddToIntsVal(int& dst1, int& dst2, int val) {
    dst1 += val;
    dst2 += val;
}*/
using namespace std;

int main()
{
    std::istringstream input {"12"
                              "CHEER 5"
                              "READ 1 10"
                              "CHEER 1"
                              "READ 2 5"
                              "READ 3 7"
                              "CHEER 2"
                              "CHEER 3"
                              "READ 3 10"
                              "CHEER 3"
                              "READ 3 11"
                              "CHEER 3"
                              "CHEER 1" };

    BookManager book_checker;
    ProcessRequests(input, std::cout, book_checker);

    /*{
        int x = 10;
        AddToIntsVal(x, x, x);
        cout << "x после AddToIntsVal: "sv << x << endl;
    }

    {
        int x = 10;
        AddToIntsRef(x, x, x);
        cout << "x после AddToIntsRef: "sv << x << endl;
    }*/
}
