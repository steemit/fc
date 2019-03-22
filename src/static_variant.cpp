#include <fc/static_variant.hpp>


namespace fc { namespace impl {

dynamic_storage::dynamic_storage() : storage(nullptr) {};

dynamic_storage::~dynamic_storage()
{
    release();
}

void* dynamic_storage::data() const
{
    FC_ASSERT( storage != nullptr );
    return (void*)storage;
}

void dynamic_storage::alloc( size_t size )
{
    release();
    storage = new char[size];
}

void dynamic_storage::release()
{
    delete [] storage;
    storage = nullptr;
}

}}
