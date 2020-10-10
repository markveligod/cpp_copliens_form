/*
**==========================
**         Includes
**==========================
*/
# include <iostream>
# include <fstream> //ifstream ofstream
# include <sstream> //stringstream
# include <cctype> // islower

/*
**==========================
**         Colors
**==========================
*/
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define RESET "\033[0m"

/*
**==========================
**         Errors
**==========================
*/
# define ERR_ARG 1
# define ERR_OPEN 2
# define ERR_UP 3

int print_error(int code)
{
    std::string array[] = {"NULL", "Invalid number of arguments\n", "Unable to open file\n", "The first letter must be uppercase\n"};
    std::cout << RED << "[Error]: Code: " << YELLOW << "[" << code << "] " << RESET << array[code];
    return (code);
}

std::string set_cpp(std::string name_class)
{
    std::stringstream os;

    os << "#include \"" << name_class << ".hpp\"\n\n";
    os << name_class << "::" << name_class << "()\n" << "{\n\n}\n\n";
    os << name_class << "::" << name_class << "(" << name_class << " const &other)\n{\n\n}\n\n";
    os << name_class << "::~" << name_class << "()\n" << "{\n\n}\n\n";
    os << name_class << " &" << name_class << "::operator=(" << name_class << " const &other)\n{\n\n\n\treturn(*this);\n}\n\n";
    return (os.str());
}

std::string set_hpp(std::string name_class)
{
    std::stringstream os;

    os << "#pragma once\n\n";
    os << "/*\n**==========================\n**\t\tIncludes\n**==========================\n*/\n\n\n";
    os << "class " << name_class << "\n";
    os << "{\n\tprivate:\n\n\tpublic:\n";
    os << "\t\t" << name_class << "();\n";
    os << "\t\t" << name_class << "(" << name_class << " const &other);\n";
    os << "\t\t~" << name_class << "();\n\n";
    os << "\t\t" << name_class << " &operator=(" << name_class << " const &other);\n\n";
    os << "};\n";
    return (os.str());
}

int create_class(std::string name_class)
{
    std::ofstream out_file_cpp;
    std::ofstream out_file_hpp;

    out_file_cpp.open(name_class + ".cpp", std::ios::trunc);
    out_file_hpp.open(name_class + ".hpp", std::ios::trunc);
    if (!out_file_cpp.is_open() || !out_file_hpp.is_open())
        return (ERR_OPEN);
    out_file_cpp << set_cpp(name_class);
    out_file_hpp << set_hpp(name_class);
    std::cout << GREEN << "[Success]: " << RESET << "the file " << YELLOW << name_class + ".cpp" << " " << name_class + ".hpp" << RESET << " is created\n";
    return (0);
}

int main(int ac, char **av)
{
    int status = 0;
    int i;

    if (ac == 1)
        return (print_error(ERR_ARG));
    for (i = 1; i < ac; i++)
        if (islower(av[i][0]))
            return (print_error(ERR_UP));
    for (i = 1; i < ac; i++)
        if ((status = create_class(av[i])) != 0)
            return (print_error(status));
    return (status);
}
