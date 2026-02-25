// This file contains bindings for the flow functions

// It is expected, that the #include statemnts can raise errors in your IDE.
// The needed files for those imports are only provided during the build process.

extern "C" {
    #include <topotoolbox.h>
}

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

namespace py = pybind11;

void wrap_drainagebasins(py::array_t<ptrdiff_t> basins,
                         py::array_t<ptrdiff_t> source,
                         py::array_t<ptrdiff_t> target,
                         std::tuple<ptrdiff_t, ptrdiff_t> dims) {
  ptrdiff_t *basins_ptr = basins.mutable_data();
  ptrdiff_t *source_ptr = source.mutable_data();
  ptrdiff_t *target_ptr = target.mutable_data();
  ptrdiff_t edge_count = source.size();
  ptrdiff_t dims_array[2] = {std::get<0>(dims), std::get<1>(dims)};

  drainagebasins(basins_ptr, source_ptr, target_ptr, edge_count, dims_array);
}

// Make wrap_funcname() function available as grid_funcname() to be used by
// by functions in the pytopotoolbox package

PYBIND11_MODULE(_flow, m) {
  m.def("drainagebasins", &wrap_drainagebasins);
}
