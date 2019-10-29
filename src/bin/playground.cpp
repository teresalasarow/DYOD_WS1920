#include <iostream>
#include <vector>

#include "../lib/storage/base_segment.hpp"
#include "../lib/storage/chunk.hpp"
#include "../lib/utils/assert.hpp"

int main() {
  opossum::Assert(true, "We can use opossum files here :)");
  std::cout << "Playground wird gestartet!\n" << std::endl;

  opossum::Chunk c;

  std::shared_ptr<opossum::BaseSegment> int_value_segment = nullptr;
  std::shared_ptr<opossum::BaseSegment> string_value_segment = nullptr;
  std::vector<std::shared_ptr<opossum::BaseSegment>> chunk_segment;
  std::vector<opossum::AllTypeVariant> value_list = {1, "one", 2, "two"};
  //std::vector<opossum::AllTypeVariant> value_list = {1, "one", 2, "two", 3, "three", 4, "four"};

  std::cout << "chunk.row: " << c.size() << std::endl;
  c.add_segment(int_value_segment);
  chunk_segment.insert(chunk_segment.end(), int_value_segment);
  std::cout << "chunk.row: " << c.size() << std::endl;
  c.add_segment(string_value_segment);
  chunk_segment.insert(chunk_segment.end(), string_value_segment);
  std::cout << "chunk.row: " << c.size() << std::endl;
  c.add_segment(int_value_segment);
  chunk_segment.insert(chunk_segment.end(), string_value_segment);
  std::cout << "chunk.row: " << c.size() << std::endl;
  c.add_segment(string_value_segment);
  chunk_segment.insert(chunk_segment.end(), int_value_segment);
  std::cout << "chunk.row: " << c.size() << std::endl;
  std::cout << "\n\n";

  //c.append(value_list);
  //std::cout << "c.size(): " << c.size() << std::endl;
  // for (int i = 0u; i < c.size(); ++i) {
  //   auto seg = c.get_segment(opossum::ColumnID{i});
  //   for (auto val : value_list) {
  //     auto seg = std::make_shared<opossum::BaseSegment>(val);
  //   }
  // }

  for (auto i = chunk_segment.begin(); i != chunk_segment.end(); ++i) {
    for (auto j = value_list.begin(); j != value_list.end(); ++j) {
      std::cout << "[1] " << std::endl;
      const auto& base_value_segment = std::shared_ptr<opossum::BaseSegment>(*i);
      std::cout << "[2] " << std::endl;
      DebugAssert(base_value_segment, "Can't append to segment that is not a ValueSegment");
      std::cout << "[3] (und *j)" << *j << std::endl;
      if (base_value_segment != NULL) {
        base_value_segment->append(*j);
        std::cout << "[4] " << std::endl;
      }
    }
  }

  auto seg1 = c.get_segment(opossum::ColumnID{1u});
  //auto seg2 = c.get_segment(opossum::ColumnID{2u});
  // auto seg3 = c.get_segment(opossum::ColumnID{3u});
  // auto seg4 = c.get_segment(opossum::ColumnID{4u});

  std::cout << "seg1 = " << &seg1 << std::endl;
  // std::cout << "seg2 = " << &seg2 << std::endl;
  // std::cout << "seg3 = " << &seg3 << std::endl;
  // std::cout << "seg4 = " << &seg4 << std::endl;

  int counter = 1;

  for (auto val : value_list) {
    std::cout << "get val = " << val << std::endl;
    //std::shared_ptr<opossum::BaseSegment> pointer = std::make_shared<opossum::BaseSegment>(val);
    std::shared_ptr<int> pointer = std::make_shared<int>(414);
    //std::shared_ptr<opossum::BaseSegment> op_pointer = std::make_shared<opossum::BaseSegment>(1);

    //&seg = make_shared<opossum::AllTypeVariant>(*pointer);
    //std::shared_ptr<opossum::BaseSegment> pointer = std::make_shared<opossum::BaseSegment>(val);
    std::cout << "round " << ++counter;
    std::cout << " &seg " << &seg1 << std::endl;
    std::cout << "*pointer " << &pointer << std::endl;

    //std::cout << "Value " << &seg << " from position " << ++counter << " is added to segment.\n" << std::endl;
  }

  // for (auto list : c) {
  //   for (auto value : list) {
  //     std::cout << value << " ";
  //   }
  //   //std::cout << "\n";
  //   std::cout << "\n";
  // }

  // using a variable type of initializer_list
  std::initializer_list<char> row = {'a', 'b', 'c'};
  std::vector<std::initializer_list<char>> vec{row};

  row = {'d', 'e', 'f', 'g', 'h', 'i'};  // change list
  std::cout << "row1: " << row.size() << std::endl;

  vec.push_back(row);  // add rows
  vec.push_back({'g', 'h', 'i'});

  row = {'j', 'k', 'l'};
  vec.push_back(row);
  vec.push_back({'m', 'n', 'o'});

  std::cout << "row2: " << row.size() << std::endl;

  for (auto list : vec) {
    for (auto value : list) {
      std::cout << value << " ";
    }
    //std::cout << "\n";
    std::cout << "\n";
  }

  std::cout << "\nAnzahl rows: " << vec.size();
  std::cout << "\nAnzahl columns: " << vec[1].size();

  //access without looping
  // pointer to first row, first element (value: 1)
  const char* elementA = vec[0].begin();
  elementA += 3;  // point to second row, first element (value: 4)
  std::cout << "\nElementA(" << *elementA << ")\n";

  const char* elementB = vec[0].end();
  std::cout << "\nElementB(" << *elementB << ")\n";

  // access the same element with x,y coords = (0,1)
  int x = 0, y = 1;
  std::cout << "\ncoord(0,1) = " << *(vec[y].begin() + x) << "\n";

  return 0;
}
