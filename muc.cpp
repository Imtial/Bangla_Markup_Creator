#include <iostream>
#include <fstream>
#include <locale>
#include <vector>
#include <utility>
#include <cstdlib>
using namespace std;

#define VERSION "1.0.2"

int num_started_with(wstring& str)
{
    int num = 0;

    int i;

    for (i = 0; i < str.length() && str[i] != L')' && str[i] != L'.' && str[i] != L'।'; i++)
    {
        switch (str[i])
        {
            case L'০':
                num = 10 * num + 0;
                break;
            case L'১':
                num = 10 * num + 1;
                break;
            case L'২':
                num = 10 * num + 2;
                break;
            case L'৩':
                num = 10 * num + 3;
                break;
            case L'৪':
                num = 10 * num + 4;
                break;
            case L'৫':
                num = 10 * num + 5;
                break;
            case L'৬':
                num = 10 * num + 6;
                break;
            case L'৭':
                num = 10 * num + 7;
                break;
            case L'৮':
                num = 10 * num + 8;
                break;
            case L'৯':
                num = 10 * num + 9;
                break;
            case L' ':
                break;
            case L'\t':
                break;
            default:
                return -1;
        }
    }
    if (num == 0) return -1; // if leading num is unchanged, don't consider it
    str = str.substr(i + 1);
    return num;
}

class Producer
{
protected:
    wofstream file;
    string filename;
    wstring& title;
    wstring& author;
    wstring& date;
    vector<pair<int, wstring>>& vec_lines;
    vector<wstring>& section_titles;
    vector<vector<wstring>>& lists;
public:
    Producer(string filename, wstring& title, wstring& author, wstring& date, vector<pair<int, wstring>>& vec_lines, vector<wstring>& section_titles, vector<vector<wstring>>& lists);
    virtual void produce() = 0;
    virtual void insert_list(wstring info) = 0;
    virtual ~Producer();
};

Producer::Producer(string filename, wstring& title, wstring& author, wstring& date, vector<pair<int, wstring>>& vec_lines, vector<wstring>& section_titles, vector<vector<wstring>>& lists)
    : title(title)
    , author(author)
    , date(date)
    , vec_lines(vec_lines)
    , section_titles(section_titles)
    , lists(lists)
{
    this->filename = filename.substr(0, filename.find_last_of('.'));

    locale loc("bn_BD.UTF-8");
    file.imbue(loc);
}

Producer::~Producer()
{
    if (file.is_open()) file.close();
}


class HtmlProducer : public Producer
{
private:
    void insert_list(wstring info);
public:
    HtmlProducer(string filename, wstring& title, wstring& author, wstring& date, vector<pair<int, wstring>>& vec_lines, vector<wstring>& section_titles, vector<vector<wstring>>& lists);
    void produce();
    ~HtmlProducer();
};

HtmlProducer::HtmlProducer(string filename, wstring& title, wstring& author, wstring& date, vector<pair<int, wstring>>& vec_lines, vector<wstring>& section_titles, vector<vector<wstring>>& lists) 
: Producer(filename, title, author, date, vec_lines, section_titles, lists)
{
    file.open(this->filename + ".html");
}

void HtmlProducer::insert_list(wstring info)
{
    int list_index = stoi(info.substr(4)) - 1; // lIsT has 4 chars
    file << "<ol style=\"list-style-type:bengali;\">" << endl;
    for (vector<wstring>::iterator it = lists[list_index].begin(); it != lists[list_index].end(); ++it)
    {
        file << "<li>" << (*it) << "</li>" << endl;
    }
    file << "</ol>" << endl;
}

void HtmlProducer::produce()
{
    string nl("\n");
    wstring wnl(nl.begin(), nl.end());
    bool p_opened = false;

    file << "<!DOCTYPE html>" << endl;
    file << "<html lang=\"en\">" << endl;
    file << "<head>" << endl;
    file << "<meta charset=\"UTF-8\">" << endl;
    file << "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">" << endl;
    file << "<link rel=\"stylesheet\" href=\"https://stackpath.bootstrapcdn.com/bootstrap/4.5.0/css/bootstrap.min.css\" integrity=\"sha384-9aIt2nRpC12Uk9gS9baDl411NQApFmC26EwAOH8WgZl5MYYxFfc+NcPb1dKGj7Sk\" crossorigin=\"anonymous\">" << endl;
    file << "<title>" << title << "</title>" << endl;
    file << "</head>" << endl;
    file << "<body>" << endl;
    file << "<div class=\"container\">" << endl;    // container div open
    file << "<div class=\"jumbotron text-center\">" << endl;    // jumbotron div open
    file << "<h1 class=\"display-3\">" << title << "</h1>" << endl;
    file << "<h1 class=\"lead\">" << author << "</h1>" << endl;
    file << "</div>" << endl;                                   // jumbotron div close

    for(int i = 0; i < vec_lines.size(); i++)
    {
        if (i == 0)
        {
            if (vec_lines[i].first)
            {
                file << "<h2>" << section_titles[vec_lines[i].first] << "</h2>" << endl;
            }
            file << "<p>"; p_opened = true;
        }
        else
        {
            if (vec_lines[i].first > vec_lines[i-1].first)
            {
                file << "<h2>" << section_titles[vec_lines[i].first - 1] << "</h2>" << endl;
                file << "<p>"; p_opened = true;
            }
        }

        if (vec_lines[i].second != wnl)
        {
            if (vec_lines[i].second.substr(0, 4) == L"lIsT") insert_list(vec_lines[i].second);
            else file << vec_lines[i].second << endl;
        }
        else
        {
            if (p_opened)
            {
                file << "</p>" << endl; p_opened = false;
            }
            if (i != vec_lines.size() - 1)
            {
                file << "<p>"; p_opened = true;
            }
        }
        

        if (i + 1 < vec_lines.size() && vec_lines[i].first < vec_lines[i+1].first)
        {
            file << "</p>" << endl; p_opened = false;
        }
    }

    if (p_opened) file << "</p>" << endl;
    file << "<div style=\"text-align: right; font-style: italic; padding: 4em 4em 4em 4em;\">" << date << "</div>" << endl;
    file << "</div>" << endl;                       // container div close
    file << "<script src=\"https://code.jquery.com/jquery-3.5.1.slim.min.js\" integrity=\"sha384-DfXdz2htPH0lsSSs5nCTpuj/zy4C+OGpamoFVy38MVBnE+IbbVYUew+OrCXaRkfj\" crossorigin=\"anonymous\"></script>" << endl;
    file << "<script src=\"https://cdn.jsdelivr.net/npm/popper.js@1.16.0/dist/umd/popper.min.js\" integrity=\"sha384-Q6E9RHvbIyZFJoft+2mJbHaEWldlvI9IOYy5n3zV9zzTtmI3UksdQRVvoxMfooAo\" crossorigin=\"anonymous\"></script>" << endl;
    file << "<script src=\"https://stackpath.bootstrapcdn.com/bootstrap/4.5.0/js/bootstrap.min.js\" integrity=\"sha384-OgVRvuATP1z7JjHLkuOU7Xw704+h835Lr+6QL9UvYjZE3Ipu6Tp75j7Bh/kR0JKI\" crossorigin=\"anonymous\"></script>" << endl;
    file << "</body>" << endl;
    file << "</html>" << endl;
}

HtmlProducer::~HtmlProducer()
{
    
}

class TexProducer : public Producer
{
private:
    void insert_list(wstring info);
public:
    TexProducer(string filename, wstring& title, wstring& author, wstring& date, vector<pair<int, wstring>>& vec_lines, vector<wstring>& section_titles, vector<vector<wstring>>& lists);
    void produce();
    ~TexProducer();
};

TexProducer::TexProducer(string filename, wstring& title, wstring& author, wstring& date, vector<pair<int, wstring>>& vec_lines, vector<wstring>& section_titles, vector<vector<wstring>>& lists)
: Producer(filename, title, author, date, vec_lines, section_titles, lists)
{
    file.open(this->filename + ".tex");
}

void TexProducer::insert_list(wstring info)
{
    int list_index = stoi(info.substr(4)) - 1;
    file << "\\begin{enumerate}" << endl;
    for (vector<wstring>::iterator it = lists[list_index].begin(); it != lists[list_index].end(); ++it)
    {
        file << "\\item " << (*it) << endl;
    }
    file << "\\end{enumerate}" << endl;
    file << "\\par" << endl;
}

void TexProducer::produce()
{
    wstring wnl = L"\n";

    file << "\\documentclass[12pt]{article}" << endl;
    file << "\\usepackage[banglamainfont=Kalpurush,banglattfont=Siyam Rupali]{latexbangla}" << endl;
    file << "\\usepackage[T1]{fontenc}" << endl;
    file << "\\usepackage{geometry}" << endl;
    file << "\\geometry{top=20mm,left=20mm,right=20mm,bottom=20mm}" << endl;
    file << "\\renewcommand{\\thepage}{\\tobangla{page}}" << endl;
    file << "\\renewcommand{\\thesection}{\\tobangla{section}}" << endl;
    file << "\\renewcommand{\\thesubsection}{\\thesection.\\tobangla{subsection}}" << endl;

    file << "\\title{" << title << "}" << endl;
    file << "\\author{" << author << "}" << endl;
    file << "\\date{" << date << "}" << endl;
    file << "\\begin{document}" << endl;
    file << "\\maketitle" << endl;

    for (int i = 0; i < vec_lines.size(); i++)
    {
        if (i == 0 && vec_lines[i].first)
        {
            file << "\\section{" << section_titles[vec_lines[i].first - 1] << "}" << endl;
        }
        else if (vec_lines[i].first > vec_lines[i-1].first)
        {
            file << "\\section{" << section_titles[vec_lines[i].first - 1] << "}" << endl;
        }

        if (vec_lines[i].second != wnl)
        {
            if (vec_lines[i].second.substr(0, 4) == L"lIsT") insert_list(vec_lines[i].second);
            else file << vec_lines[i].second << endl;
        }
        else file << "\\newline\\par" << endl;
    }

    file << "\\end{document}";
}

TexProducer::~TexProducer()
{
}


int main(int argc, char * argv[])
{
    ios::sync_with_stdio(false);

    locale loc("bn_BD.UTF-8");
    wcout.imbue(loc);

    vector<string> input_files;
    bool html_flag = true;
    bool tex_flag = true;
    bool pdf_flag = false;
    
    if (argc == 1)
    {
        cout << "Please provide at least one input file" << endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        for (int i = 1; i < argc; i++)
        {
            string fname(argv[i]);
            if (fname == "-v" || fname == "--version")
            {
                cout << VERSION << endl;
                continue;
            }
            if (fname == "-pdf")
            {
                if (system("which xelatex > /dev/null 2>&1"))
                {
                    cout << "ERROR: xelatex IS NOT FOUND IN YOUR SYSTEM. PDF CONVERSION IS NOT POSSIBLE" << endl;
                }
                else pdf_flag = true;
                continue;
            }

            if (fname.substr(fname.find_last_of('.')) == ".txt") input_files.push_back(fname);
            else cout << "WARNING: " << fname << " IS NOT A TEXT FILE. WE CANNOT CONVERT THIS." << endl;
        }
    }
    
    for (vector<string>::iterator it = input_files.begin(); it != input_files.end(); ++it)
    {
        wifstream in;
        in.imbue(loc);
        string file_name = (*it);
        in.open(file_name.c_str());

        vector<pair<int, wstring>> vec_lines;
        vector<wstring> section_titles;
        vector<wstring> list_items;
        vector<vector<wstring>> lists;
        wstring title = L"", author = L"", date = L"";
        int sec_count = 0;
        bool is_body_started = false;
        int list_count  = 0;
        int list_state = 0;
        wstring newline = L"\n";

        for (wstring str; getline(in, str); )
        {
            if (is_body_started)
            {
                if (str[0] == '#')
                {
                    if (list_state)
                    {
                        list_state = 0;
                        lists.push_back(list_items);
                    }
                    section_titles.push_back(str.substr(1));
                    sec_count++;

                    while (vec_lines.back().second == newline)
                    {
                        vec_lines.pop_back();
                    }
                }
                else if (str.empty())
                {
                    if(list_state == 0 && vec_lines.back().second != newline && vec_lines.front() != vec_lines.back())
                    {
                        vec_lines.push_back(make_pair(sec_count, newline));
                    }
                }
                else
                {
                    int starting_num = num_started_with(str);
                    if (list_state == 0 && starting_num == 1)
                    {
                        list_count++;
                        list_state = 1;
                        list_items.clear();
                        list_items.push_back(str);
                        vec_lines.push_back(make_pair(sec_count, L"lIsT"+to_wstring(list_count)));
                    }
                    else if (list_state == 1)
                    {
                        if (starting_num == -1)
                        {
                            list_state = 0;
                            lists.push_back(list_items);
                            vec_lines.push_back(make_pair(sec_count, str));
                        }
                        else
                        {
                            list_items.push_back(str);
                        }
                        
                    }
                    else vec_lines.push_back(make_pair(sec_count, str));
                }

            }
            else
            {
                if (str[0] == '$')
                {
                    title = str.substr(1);
                }
                if (str[0] == '@')
                {
                    author = str.substr(1);
                }
                if (str[0] == '>')
                {
                    date = str.substr(1);
                }
                if (str[0] == '%')
                {
                    is_body_started = true;
                }
            }
        }
        if (list_state) lists.push_back(list_items);
        in.close();

        Producer * producer;
        producer = new HtmlProducer (file_name, title, author, date, vec_lines, section_titles, lists);
        producer->produce();
        delete producer;

        producer = new TexProducer (file_name, title, author, date, vec_lines, section_titles, lists);
        producer->produce();
        delete producer;

        if (pdf_flag)
        {
            string cmd = "xelatex " + file_name.substr(0, file_name.find_last_of('.')) + ".tex";
            cout << cmd << endl;
            int exit_code = system(cmd.c_str());
            if (exit_code/256 == 0)
            {
                system(cmd.c_str());
                system("rm *.log *.aux *.out");
            }
            else
            {
                cout << "ERROR: PDF COMPILATION FAILED." << endl;
            }
        }

    }
    return 0;
}
