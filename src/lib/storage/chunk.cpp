#include <iomanip>
#include <iterator>
#include <limits>
#include <memory>
#include <mutex>
#include <string>
#include <utility>
#include <vector>

#include "base_segment.hpp"
#include "chunk.hpp"

#include "utils/assert.hpp"

namespace opossum {

void Chunk::add_segment(std::shared_ptr<BaseSegment> segment) {
  //chunk.push_back(segment);
  chunk_segment.insert(chunk_segment.end(), segment);
}

void Chunk::append(const std::vector<AllTypeVariant>& values) {
  for (auto i = chunk_segment.begin(); i != chunk_segment.end(); ++i) {
    for (auto j = values.begin(); j != values.end(); ++j) {
      const auto& base_value_segment = std::shared_ptr<BaseSegment>(*i);
      DebugAssert(base_value_segment, "Can't append to segment that is not a ValueSegment");
      base_value_segment->append(*j);
    }
  }
}

std::shared_ptr<BaseSegment> Chunk::get_segment(ColumnID column_id) const { return chunk_segment.at(column_id); }

uint16_t Chunk::column_count() const {
  // Implementation goes here
  //return (unsigned)chunk[0].size();
  //chunk[0];
  return 0;
}

uint32_t Chunk::size() const {
  if (chunk_segment.empty()) {
    return 0;
  }
  return (unsigned)chunk_segment.size();
}

}  // namespace opossum
