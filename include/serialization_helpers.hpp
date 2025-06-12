#ifndef SERIALIZATION_HELPERS_HPP
#define SERIALIZATION_HELPERS_HPP

#include <vector>
#include <type_traits>
#include <cstring>
#include <vsomeip/vsomeip.hpp>

namespace serialization {

template <typename T>
std::vector<vsomeip::byte_t> serializeStruct(const T& data) {
    static_assert(std::is_trivially_copyable<T>::value, "Struct must be trivially copyable");

    const vsomeip::byte_t* ptr = reinterpret_cast<const vsomeip::byte_t*>(&data);
    return std::vector<vsomeip::byte_t>(ptr, ptr + sizeof(T));
}

// Generic deserialization function
template <typename T>
T deserializeStruct(const std::vector<vsomeip::byte_t>& payload) {
    static_assert(std::is_trivially_copyable<T>::value, "Struct must be trivially copyable");
    T data;
    std::memcpy(&data, payload.data(), sizeof(T));
    return data;
}

// Utility function to extract vector from vsomeip payload and deserialize
template <typename T>
T extractAndDeserialize(const std::shared_ptr<vsomeip::payload>& payload_ptr) {
    std::vector<vsomeip::byte_t> payload(payload_ptr->get_data(),
                                         payload_ptr->get_data() + payload_ptr->get_length());
    return deserializeStruct<T>(payload);
}

} // namespace serialization

#endif // SERIALIZATION_HELPERS_HPP
