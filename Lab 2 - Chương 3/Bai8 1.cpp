#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Lớp đại diện cho một phim
class Movie {
public:
    string title;        // Tiêu đề phim
    string genre;        // Thể loại phim
    string director;     // Đạo diễn
    string mainActor;    // Diễn viên chính nam
    string mainActress;  // Diễn viên chính nữ
    int year;            // Năm phát hành
    Movie* next;         // Con trỏ đến phim tiếp theo

    // Constructor khởi tạo thông tin phim
    Movie(string t, string g, string d, string ma, string ma2, int y)
        : title(t), genre(g), director(d), mainActor(ma), mainActress(ma2), year(y), next(nullptr) {}
};

// Lớp quản lý danh sách phim
class MovieList {
private:
    Movie* head; // Con trỏ đến phim đầu tiên trong danh sách

public:
    MovieList() : head(nullptr) {} // Constructor khởi tạo danh sách phim rỗng

    // Thêm một phim vào danh sách
    void addMovie(string title, string genre, string director, string mainActor, string mainActress, int year) {
        Movie* newMovie = new Movie(title, genre, director, mainActor, mainActress, year);
        if (!head) {
            head = newMovie;
        } else {
            Movie* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newMovie;
        }
    }

    // Tải danh sách phim từ tệp
    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Không thể mở tệp " << filename << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string title, genre, director, mainActor, mainActress, yearStr;
            getline(ss, title, '#');
            getline(ss, genre, '#');
            getline(ss, director, '#');
            getline(ss, mainActor, '#');
            getline(ss, mainActress, '#');
            getline(ss, yearStr, '#');
            int year = stoi(yearStr);

            addMovie(title, genre, director, mainActor, mainActress, year);
        }
        file.close();
    }

    // Lưu danh sách phim vào tệp
    void saveToFile(const string& filename) {
        ofstream file(filename);
        if (!file.is_open()) {
            cerr << "Không thể mở tệp " << filename << endl;
            return;
        }

        Movie* current = head;
        while (current) {
            file << current->title << "#" << current->genre << "#" << current->director << "#"
                 << current->mainActor << "#" << current->mainActress << "#" << current->year << endl;
            current = current->next;
        }
        file.close();
    }

    // Cập nhật thể loại của một phim
    void updateGenre(const string& title, const string& newGenre) {
        Movie* current = head;
        while (current) {
            if (current->title == title) {
                current->genre = newGenre;
                break;
            }
            current = current->next;
        }
    }

    // In danh sách phim ra màn hình
    void printList() {
        Movie* current = head;
        while (current) {
            cout << current->title << " | " << current->genre << " | " << current->director << " | "
                 << current->mainActor << " | " << current->mainActress << " | " << current->year << endl;
            current = current->next;
        }
    }

    // Lưu các phim theo diễn viên chính vào tệp
    void saveMoviesByActor(const string& actor) {
        ofstream file(actor + ".txt");
        if (!file.is_open()) {
            cerr << "Không thể mở tệp " << actor << ".txt" << endl;
            return;
        }

        Movie* current = head;
        while (current) {
            if (current->mainActor == actor) {
                file << current->title << "#" << current->genre << "#" << current->director << "#"
                     << current->mainActor << "#" << current->mainActress << "#" << current->year << endl;
            }
            current = current->next;
        }
        file.close();
    }

    // Lưu các phim theo đạo diễn vào các tệp riêng biệt
    void saveMoviesByDirector() {
        Movie* current = head;
        while (current) {
            ofstream file(current->director + ".txt", ios::app);
            if (!file.is_open()) {
                cerr << "Không thể mở tệp " << current->director << ".txt" << endl;
                return;
            }

            file << current->title << "#" << current->genre << "#" << current->director << "#"
                 << current->mainActor << "#" << current->mainActress << "#" << current->year << endl;
            file.close();

            current = current->next;
        }
    }

    // Lưu ba phim mới nhất vào tệp "Phimmoi.txt"
    void saveNewestMovies() {
        vector<Movie*> movies;
        Movie* current = head;
        while (current) {
            movies.push_back(current);
            current = current->next;
        }

        sort(movies.begin(), movies.end(), [](Movie* a, Movie* b) {
            return a->year > b->year;
        });

        ofstream file("Phimmoi.txt");
        if (!file.is_open()) {
            cerr << "Không thể mở tệp Phimmoi.txt" << endl;
            return;
        }

        for (size_t i = 0; i < 3 && i < movies.size(); ++i) {
            file << movies[i]->title << "#" << movies[i]->genre << "#" << movies[i]->director << "#"
                 << movies[i]->mainActor << "#" << movies[i]->mainActress << "#" << movies[i]->year << endl;
        }
        file.close();
    }
};

// Hiển thị menu lựa chọn
void displayMenu() {
    cout << "---------------------MENU---------------------" << endl;
    cout << "1. Tải phim từ tệp" << endl;
    cout << "2. Cập nhật thể loại phim" << endl;
    cout << "3. In danh sách phim" << endl;
    cout << "4. Lưu phim theo diễn viên chính" << endl;
    cout << "5. Lưu phim theo đạo diễn" << endl;
    cout << "6. Lưu phim mới nhất" << endl;
    cout << "7. Thoát" << endl;
    cout << "----------------------------------------------" << endl;
}

int main() {
    MovieList movieList;
    int choice;

    while (true) {
        displayMenu();
        cout << "Nhập lựa chọn của bạn: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            {
                string filename;
                cout << "Nhập tên tệp đầu vào: ";
                getline(cin, filename);
                movieList.loadFromFile(filename);
                break;
            }
        case 2:
            {
                string title, newGenre;
                cout << "Nhập tiêu đề phim: ";
                getline(cin, title);
                cout << "Nhập thể loại mới (Hành động, Tình cảm, Hài): ";
                getline(cin, newGenre);
                movieList.updateGenre(title, newGenre);
                movieList.saveToFile("Input.txt");
                break;
            }
        case 3:
            movieList.printList();
            break;
        case 4:
            {
                string actor;
                cout << "Nhập tên diễn viên chính: ";
                getline(cin, actor);
                movieList.saveMoviesByActor(actor);
                break;
            }
        case 5:
            movieList.saveMoviesByDirector();
            break;
        case 6:
            movieList.saveNewestMovies();
            break;
        case 7:
            cout << "Đang thoát chương trình." << endl;
            return 0;
        default:
            cout << "Lựa chọn không hợp lệ. Vui lòng thử lại." << endl;
        }
    }

    return 0;
}
