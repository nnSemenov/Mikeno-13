add_subdirectory(renumberMethods)

# In wmake, SloanRenumber is deprecated due to dependency problem. It's resurrected in cmake
# The old comment says:
#
## Deprecate SloanRenumber due to dependency on BOOST causing build and
## installation problems on a range of legacy systems.
add_subdirectory(SloanRenumber)

set(FOAM_regular_libraries ${FOAM_regular_libraries} PARENT_SCOPE)
