/*
**==========================
**         Includes
**==========================
*/
# include <iostream>
# include <fstream> //ifstream ofstream
# include <sstream> //stringstream

/*
**==========================
**         Colors
**==========================
*/
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define CYAN "\033[1;36m"
# define RESET "\033[0m"

/*
**==========================
**       Namespaces
**==========================
*/
using namespace std;

/*
**==========================
**         Errors
**==========================
*/
# define ERR_ARG 1
# define ERR_OPEN 2

int print_error(int code)
{
    string array[] = {NULL, "Invalid number of arguments\n", "Unable to open file\n"};
    cout << "[" << RED << "ERROR" << RESET << "]: " << RED << "Code: " << RESET << code << " " << array[code];
    return (code);
}

string set_cpp(string &name_class)
{
    stringstream os;

    os << "#include \"" << name_class << ".hpp\"\n\n";
    os << name_class << "::" << name_class << "()\n" << "{\n\n}\n\n";
    os << name_class << "::" << name_class << "(" << name_class << " const &other)\n{\n\n}\n\n";
    os << name_class << "::~" << name_class << "()\n" << "{\n\n}\n\n";
    os << name_class << " &" << name_class << "::operator=(" << name_class << " const &other)\n{\n\n\n\treturn(*this);\n}\n\n";
    return (os.str());
}

string set_hpp(string &name_class)
{
    stringstream os;

    os << "#pragma once\n\n";
    os << ""
}

int create_class(string name_class)
{
    ofstream out_file_cpp;
    ofstream out_file_hpp;

    out_file_cpp.open(name_class + ".cpp", ios::trunc);
    out_file_hpp.open(name_class + ".hpp", ios::trunc);
    if (!out_file_cpp.is_open() || !out_file_hpp.is_open())
        return (ERR_OPEN);
    out_file_cpp << set_cpp(name_class);
    set_hpp(name_class);
    return (0);
}

int main(int ac, char **av)
{
    int status = 0;

    if (ac < 2)
        return (print_error(1));
    for (int i = 1; i < ac; i++)
        if ((status = create_class(av[i])) != 0)
            return (print_error(status));
    return (status);
}