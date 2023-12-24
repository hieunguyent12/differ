#include <iostream>
#include <fstream>
#include <vector>
#include "utils.h"

struct Arguments
{
  std::string file1{};
  std::string file2{};
  std::string output_file{};
};

Arguments parse(char *args[])
{
  Arguments _args{};

  _args.file1 = args[1];
  _args.file2 = args[2];
  _args.output_file = args[3];

  return _args;
}

std::vector<std::string> load_file(std::string name)
{
  std::ifstream file{name};
  std::vector<std::string> content;

  if (!file)
  {
    std::cerr << "Unable to open file " << name;
    return {};
  }

  while (!file.eof())
  {
    std::string s = "";
    std::getline(file, s);
    content.push_back(s);
  }

  return content;
}

std::string construct_diff_string(int line_num, std::string file1_content, std::string file2_content)
{
  std::string result = "";
  result += utils::repeat('=', 5);
  result += "CHANGES";
  result += utils::repeat('=', 5);
  result += "\n";
  result += "file 1 " + utils::repeat('-', 5) + "\n";
  result += file1_content + "\n";
  result += utils::repeat('-', 5) + "\n";
  result += "file 2 " + utils::repeat('-', 5) + "\n";
  result += file2_content + "\n";
  result += utils::repeat('-', 5) + "\n";
  result += utils::repeat('=', 5);

  return result;
}

void run(Arguments &args)
{
  auto file1_content = load_file(args.file1);
  auto file2_content = load_file(args.file2);
  std::ofstream output{"result.txt"};
  int line_num = 0;

  for (const auto &line : file1_content)
  {
    if (line != file2_content[line_num])
    {
      auto s = construct_diff_string(line_num, line, file2_content[line_num]);
      output << s;
    }
    else
    {
      output << line << "\n";
    }
    line_num++;
  }
}

int main(int argc, char *argv[])
{
  if (argc < 4)
  {
    std::cerr << "Missing argumets...";

    return 0;
  }
  else if (argc > 4)
  {
    std::cerr << "Too many arguments...";

    return 0;
  }

  auto args = parse(argv);
  run(args);
}