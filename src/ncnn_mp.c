#include "py/runtime.h"
#include "py/obj.h"
#include "c_api.h"


// c_api:  const char* ncnn_version(void);
// Python: ncnn_mp.version() -> str
static mp_obj_t ncnn_mp_version(void) {
    const char* ver_str = ncnn_version();
    return mp_obj_new_str(ver_str, strlen(ver_str));
}
static MP_DEFINE_CONST_FUN_OBJ_0(ncnn_mp_version_obj, ncnn_mp_version);

// ------------------
/* allocator api */
// ------------------
// c_api:  ncnn_allocator_t ncnn_allocator_create_pool_allocator(void);
// Python: ncnn_mp.allocator_create_pool_allocator() -> int (handle)
static mp_obj_t ncnn_mp_allocator_create_pool_allocator(void) {
    ncnn_allocator_t allocator = ncnn_allocator_create_pool_allocator();
    if (!allocator) {
        return mp_const_none;  // TODO
    }
    return mp_obj_new_int_from_ptr(allocator);
}
static MP_DEFINE_CONST_FUN_OBJ_0(ncnn_mp_allocator_create_pool_allocator_obj, ncnn_mp_allocator_create_pool_allocator);

// c_api:  ncnn_allocator_t ncnn_allocator_create_unlocked_pool_allocator(void);
// Python: ncnn_mp.allocator_create_unlocked_pool() -> int (handle)
static mp_obj_t ncnn_mp_allocator_create_unlocked_pool(void) {
    ncnn_allocator_t allocator = ncnn_allocator_create_unlocked_pool_allocator();
    if (!allocator) {
        return mp_const_none;
    }
    return mp_obj_new_int_from_ptr(allocator);
}
static MP_DEFINE_CONST_FUN_OBJ_0(ncnn_mp_allocator_create_unlocked_pool_obj, ncnn_mp_allocator_create_unlocked_pool);

// c_api:  void ncnn_allocator_destroy(ncnn_allocator_t allocator);
// Python: ncnn_mp.allocator_destroy(allocator_handle)
static mp_obj_t ncnn_mp_allocator_destroy(mp_obj_t allocator_obj) {
    ncnn_allocator_t allocator = (ncnn_allocator_t)mp_obj_get_int(allocator_obj);
    if (allocator) {
        ncnn_allocator_destroy(allocator);
    }
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_1(ncnn_mp_allocator_destroy_obj, ncnn_mp_allocator_destroy);

// ------------------
/* option api */
// ------------------
// c_api:  ncnn_option_t ncnn_option_create(void);
// Python: ncnn_mp.option_create() -> int (handle)
static mp_obj_t ncnn_mp_option_create(void) {
    ncnn_option_t opt = ncnn_option_create();
    return mp_obj_new_int_from_ptr(opt);
}
static MP_DEFINE_CONST_FUN_OBJ_0(ncnn_mp_option_create_obj, ncnn_mp_option_create);

// c_api:  void ncnn_option_destroy(ncnn_option_t opt);
// Python: ncnn_mp.option_destroy(opt_handle)
static mp_obj_t ncnn_mp_option_destroy(mp_obj_t opt_obj) {
    ncnn_option_t opt = (ncnn_option_t)mp_obj_get_int(opt_obj);
    ncnn_option_destroy(opt);
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_1(ncnn_mp_option_destroy_obj, ncnn_mp_option_destroy);

// c_api:  int ncnn_option_get_num_threads(const ncnn_option_t opt);
// Python: ncnn_mp.option_get_num_threads(opt_handle) -> int
static mp_obj_t ncnn_mp_option_get_num_threads(mp_obj_t opt_obj) {
    ncnn_option_t opt = (ncnn_option_t)mp_obj_get_int(opt_obj);
    int num_threads = ncnn_option_get_num_threads(opt);
    return mp_obj_new_int(num_threads);
}
static MP_DEFINE_CONST_FUN_OBJ_1(ncnn_mp_option_get_num_threads_obj, ncnn_mp_option_get_num_threads);

// c_api:  void ncnn_option_set_num_threads(ncnn_option_t opt, int num_threads);
// Python: ncnn_mp.option_set_num_threads(opt_handle, num_threads)
static mp_obj_t ncnn_mp_option_set_num_threads(mp_obj_t opt_obj, mp_obj_t num_threads_obj) {
    ncnn_option_t opt = (ncnn_option_t)mp_obj_get_int(opt_obj);
    int num_threads = mp_obj_get_int(num_threads_obj);
    ncnn_option_set_num_threads(opt, num_threads);
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_2(ncnn_mp_option_set_num_threads_obj, ncnn_mp_option_set_num_threads);

// c_api:  int ncnn_option_get_use_local_pool_allocator(const ncnn_option_t opt);
// Python: ncnn_mp.option_get_use_local_pool_allocator(opt_handle) -> int
static mp_obj_t ncnn_mp_option_get_use_local_pool_allocator(mp_obj_t opt_obj) {
    ncnn_option_t opt = (ncnn_option_t)mp_obj_get_int(opt_obj);
    int use_local_pool = ncnn_option_get_use_local_pool_allocator(opt);
    return mp_obj_new_int(use_local_pool);
}
static MP_DEFINE_CONST_FUN_OBJ_1(ncnn_mp_option_get_use_local_pool_allocator_obj, ncnn_mp_option_get_use_local_pool_allocator);

// c_api:  void ncnn_option_set_use_local_pool_allocator(ncnn_option_t opt, int use_local_pool_allocator);
// Python: ncnn_mp.option_set_use_local_pool_allocator(opt_handle, use_local_pool_allocator)
static mp_obj_t ncnn_mp_option_set_use_local_pool_allocator(mp_obj_t opt_obj, mp_obj_t use_obj) {
    ncnn_option_t opt = (ncnn_option_t)mp_obj_get_int(opt_obj);
    int use_local_pool = mp_obj_get_int(use_obj);
    ncnn_option_set_use_local_pool_allocator(opt, use_local_pool);
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_2(ncnn_mp_option_set_use_local_pool_allocator_obj, ncnn_mp_option_set_use_local_pool_allocator);

// c_api:  void ncnn_option_set_blob_allocator(ncnn_option_t opt, ncnn_allocator_t allocator);
// Python: ncnn_mp.option_set_blob_allocator(opt_handle, allocator_handle)
static mp_obj_t ncnn_mp_option_set_blob_allocator(mp_obj_t opt_obj, mp_obj_t allocator_obj) {
    ncnn_option_t opt = (ncnn_option_t)mp_obj_get_int(opt_obj);
    ncnn_allocator_t allocator = (ncnn_allocator_t)mp_obj_get_int(allocator_obj);
    ncnn_option_set_blob_allocator(opt, allocator);
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_2(ncnn_mp_option_set_blob_allocator_obj, ncnn_mp_option_set_blob_allocator);

// c_api:  void ncnn_option_set_workspace_allocator(ncnn_option_t opt, ncnn_allocator_t allocator);
// Python: ncnn_mp.option_set_workspace_allocator(opt_handle, allocator_handle)
static mp_obj_t ncnn_mp_option_set_workspace_allocator(mp_obj_t opt_obj, mp_obj_t allocator_obj) {
    ncnn_option_t opt = (ncnn_option_t)mp_obj_get_int(opt_obj);
    ncnn_allocator_t allocator = (ncnn_allocator_t)mp_obj_get_int(allocator_obj);
    ncnn_option_set_workspace_allocator(opt, allocator);
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_2(ncnn_mp_option_set_workspace_allocator_obj, ncnn_mp_option_set_workspace_allocator);

// c_api:  int ncnn_option_get_use_vulkan_compute(const ncnn_option_t opt);
// Python: ncnn_mp.option_get_use_vulkan_compute(opt_handle) -> int
static mp_obj_t ncnn_mp_option_get_use_vulkan_compute(mp_obj_t opt_obj) {
    ncnn_option_t opt = (ncnn_option_t)mp_obj_get_int(opt_obj);
    int use_vulkan = ncnn_option_get_use_vulkan_compute(opt);
    return mp_obj_new_int(use_vulkan);
}
static MP_DEFINE_CONST_FUN_OBJ_1(ncnn_mp_option_get_use_vulkan_compute_obj, ncnn_mp_option_get_use_vulkan_compute);

// c_api:  void ncnn_option_set_use_vulkan_compute(ncnn_option_t opt, int use_vulkan_compute);
// Python: ncnn_mp.option_set_use_vulkan_compute(opt_handle, use_vulkan)
static mp_obj_t ncnn_mp_option_set_use_vulkan_compute(mp_obj_t opt_obj, mp_obj_t use_vulkan_obj) {
    ncnn_option_t opt = (ncnn_option_t)mp_obj_get_int(opt_obj);
    int use_vulkan_compute = mp_obj_get_int(use_vulkan_obj);
    ncnn_option_set_use_vulkan_compute(opt, use_vulkan_compute);
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_2(ncnn_mp_option_set_use_vulkan_compute_obj, ncnn_mp_option_set_use_vulkan_compute);


// ------------------
/* mat api */
// NULL: TODO
// ------------------
// c_api:  ncnn_mat_t ncnn_mat_create(void);
// Python: ncnn_mp.mat_create() -> int (handle)
static mp_obj_t ncnn_mp_mat_create(void) {
    ncnn_mat_t mat = ncnn_mat_create();
    return mp_obj_new_int_from_ptr(mat);
}
static MP_DEFINE_CONST_FUN_OBJ_0(ncnn_mp_mat_create_obj, ncnn_mp_mat_create);

// c_api:  ncnn_mat_t ncnn_mat_create_1d(int w, ncnn_allocator_t allocator);
// Python: ncnn_mp.mat_create_1d(w, allocator) -> int (handle)
static mp_obj_t ncnn_mp_mat_create_1d(mp_obj_t w_obj, mp_obj_t allocator_obj) {
    int w = mp_obj_get_int(w_obj);
    ncnn_allocator_t allocator = (ncnn_allocator_t)mp_obj_get_int(allocator_obj);
    ncnn_mat_t mat = ncnn_mat_create_1d(w, allocator);
    if (!mat) {
        return mp_const_none;
    }
    return mp_obj_new_int_from_ptr(mat);
}
static MP_DEFINE_CONST_FUN_OBJ_2(ncnn_mp_mat_create_1d_obj, ncnn_mp_mat_create_1d);

// c_api:  ncnn_mat_t ncnn_mat_create_2d(int w, int h, ncnn_allocator_t allocator);
// Python: ncnn_mp.mat_create_2d(w, h, allocator) -> int (handle)
static mp_obj_t ncnn_mp_mat_create_2d(mp_obj_t w_obj, mp_obj_t h_obj, mp_obj_t allocator_obj) {
    int w = mp_obj_get_int(w_obj);
    int h = mp_obj_get_int(h_obj);
    ncnn_allocator_t allocator = (ncnn_allocator_t)mp_obj_get_int(allocator_obj);
    ncnn_mat_t mat = ncnn_mat_create_2d(w, h, allocator);
    if (!mat) {
        return mp_const_none;
    }
    return mp_obj_new_int_from_ptr(mat);
}
static MP_DEFINE_CONST_FUN_OBJ_3(ncnn_mp_mat_create_2d_obj, ncnn_mp_mat_create_2d);

// c_api:  ncnn_mat_t ncnn_mat_create_3d(int w, int h, int c, ncnn_allocator_t allocator);
// Python: ncnn_mp.mat_create_3d(w, h, c, allocator) -> int (handle)
static mp_obj_t ncnn_mp_mat_create_3d(mp_obj_t w_obj, mp_obj_t h_obj, mp_obj_t c_obj, mp_obj_t allocator_obj) {
    int w = mp_obj_get_int(w_obj);
    int h = mp_obj_get_int(h_obj);
    int c = mp_obj_get_int(c_obj);
    ncnn_allocator_t allocator = (ncnn_allocator_t)mp_obj_get_int(allocator_obj);
    ncnn_mat_t mat = ncnn_mat_create_3d(w, h, c, allocator);
    if (!mat) {
        return mp_const_none;
    }
    return mp_obj_new_int_from_ptr(mat);
}
static MP_DEFINE_CONST_FUN_OBJ_4(ncnn_mp_mat_create_3d_obj, ncnn_mp_mat_create_3d);

// c_api:  ncnn_mat_t ncnn_mat_create_4d(int w, int h, int d, int c, ncnn_allocator_t allocator);
// Python: ncnn_mp.mat_create_4d(w, h, d, c, allocator) -> int (handle)
static mp_obj_t ncnn_mp_mat_create_4d(mp_obj_t w_obj, mp_obj_t h_obj, mp_obj_t d_obj, mp_obj_t c_obj, mp_obj_t allocator_obj) {
    int w = mp_obj_get_int(w_obj);
    int h = mp_obj_get_int(h_obj);
    int d = mp_obj_get_int(d_obj);
    int c = mp_obj_get_int(c_obj);
    ncnn_allocator_t allocator = (ncnn_allocator_t)mp_obj_get_int(allocator_obj);
    ncnn_mat_t mat = ncnn_mat_create_4d(w, h, d, c, allocator);
    if (!mat) {
        return mp_const_none;
    }
    return mp_obj_new_int_from_ptr(mat);
}
static MP_DEFINE_CONST_FUN_OBJ_5(ncnn_mp_mat_create_4d_obj, ncnn_mp_mat_create_4d);

// c_api:  ncnn_mat_t ncnn_mat_create_external_1d(int w, void* data, ncnn_allocator_t allocator);
// Python: ncnn_mp.mat_create_external_1d(w, data, allocator) -> int (handle)
static mp_obj_t ncnn_mp_mat_create_external_1d(mp_obj_t w_obj, mp_obj_t data_obj, mp_obj_t allocator_obj) {
    int w = mp_obj_get_int(w_obj);
    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(data_obj, &bufinfo, MP_BUFFER_READ);
    ncnn_allocator_t allocator = (ncnn_allocator_t)mp_obj_get_int(allocator_obj);
    ncnn_mat_t mat = ncnn_mat_create_external_1d(w, bufinfo.buf, allocator);
    if (!mat) {
        return mp_const_none;
    }
    return mp_obj_new_int_from_ptr(mat);
}
static MP_DEFINE_CONST_FUN_OBJ_3(ncnn_mp_mat_create_external_1d_obj, ncnn_mp_mat_create_external_1d);

// c_api:  ncnn_mat_t ncnn_mat_create_external_2d(int w, int h, void* data, ncnn_allocator_t allocator);
// Python: ncnn_mp.mat_create_external_2d(w, h, data, allocator) -> int (handle)
static mp_obj_t ncnn_mp_mat_create_external_2d(mp_obj_t w_obj, mp_obj_t h_obj, mp_obj_t data_obj, mp_obj_t allocator_obj) {
    int w = mp_obj_get_int(w_obj);
    int h = mp_obj_get_int(h_obj);
    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(data_obj, &bufinfo, MP_BUFFER_READ);
    ncnn_allocator_t allocator = (ncnn_allocator_t)mp_obj_get_int(allocator_obj);
    ncnn_mat_t mat = ncnn_mat_create_external_2d(w, h, bufinfo.buf, allocator);
    if (!mat) {
        return mp_const_none;
    }
    return mp_obj_new_int_from_ptr(mat);
}
static MP_DEFINE_CONST_FUN_OBJ_4(ncnn_mp_mat_create_external_2d_obj, ncnn_mp_mat_create_external_2d);

// c_api:  ncnn_mat_t ncnn_mat_create_external_3d(int w, int h, int c, void* data, ncnn_allocator_t allocator);
// Python: ncnn_mp.mat_create_external_3d(w, h, c, data, allocator) -> int (handle)
static mp_obj_t ncnn_mp_mat_create_external_3d(mp_obj_t w_obj, mp_obj_t h_obj, mp_obj_t c_obj, mp_obj_t data_obj, mp_obj_t allocator_obj) {
    int w = mp_obj_get_int(w_obj);
    int h = mp_obj_get_int(h_obj);
    int c = mp_obj_get_int(c_obj);
    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(data_obj, &bufinfo, MP_BUFFER_READ);
    ncnn_allocator_t allocator = (ncnn_allocator_t)mp_obj_get_int(allocator_obj);
    ncnn_mat_t mat = ncnn_mat_create_external_3d(w, h, c, bufinfo.buf, allocator);
    if (!mat) {
        return mp_const_none;
    }
    return mp_obj_new_int_from_ptr(mat);
}
static MP_DEFINE_CONST_FUN_OBJ_5(ncnn_mp_mat_create_external_3d_obj, ncnn_mp_mat_create_external_3d);

// c_api:  ncnn_mat_t ncnn_mat_create_external_4d(int w, int h, int d, int c, void* data, ncnn_allocator_t allocator);
// Python: ncnn_mp.mat_create_external_4d(w, h, d, c, data, allocator) -> int (handle)
static mp_obj_t ncnn_mp_mat_create_external_4d(mp_obj_t w_obj, mp_obj_t h_obj, mp_obj_t d_obj, mp_obj_t c_obj, mp_obj_t data_obj, mp_obj_t allocator_obj) {
    int w = mp_obj_get_int(w_obj);
    int h = mp_obj_get_int(h_obj);
    int d = mp_obj_get_int(d_obj);
    int c = mp_obj_get_int(c_obj);
    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(data_obj, &bufinfo, MP_BUFFER_READ);
    ncnn_allocator_t allocator = (ncnn_allocator_t)mp_obj_get_int(allocator_obj);
    ncnn_mat_t mat = ncnn_mat_create_external_4d(w, h, d, c, bufinfo.buf, allocator);
    if (!mat) {
        return mp_const_none;
    }
    return mp_obj_new_int_from_ptr(mat);
}
static MP_DEFINE_CONST_FUN_OBJ_6(ncnn_mp_mat_create_external_4d_obj, ncnn_mp_mat_create_external_4d);

// c_api:  ncnn_mat_t ncnn_mat_create_1d_elem(int w, size_t elemsize, int elempack, ncnn_allocator_t allocator);
// Python: ncnn_mp.mat_create_1d_elem(w, elemsize, elempack, allocator) -> int (handle)
static mp_obj_t ncnn_mp_mat_create_1d_elem(mp_obj_t w_obj, mp_obj_t elemsize_obj, mp_obj_t elempack_obj, mp_obj_t allocator_obj) {
    int w = mp_obj_get_int(w_obj);
    size_t elemsize = (size_t)mp_obj_get_int(elemsize_obj);
    int elempack = mp_obj_get_int(elempack_obj);
    ncnn_allocator_t allocator = (ncnn_allocator_t)mp_obj_get_int(allocator_obj);
    ncnn_mat_t mat = ncnn_mat_create_1d_elem(w, elemsize, elempack, allocator);
    if (!mat) {
        return mp_const_none;
    }
    return mp_obj_new_int_from_ptr(mat);
}
static MP_DEFINE_CONST_FUN_OBJ_4(ncnn_mp_mat_create_1d_elem_obj, ncnn_mp_mat_create_1d_elem);

// c_api:  ncnn_mat_t ncnn_mat_create_2d_elem(int w, int h, size_t elemsize, int elempack, ncnn_allocator_t allocator);
// Python: ncnn_mp.mat_create_2d_elem(w, h, elemsize, elempack, allocator) -> int (handle)
static mp_obj_t ncnn_mp_mat_create_2d_elem(mp_obj_t w_obj, mp_obj_t h_obj, mp_obj_t elemsize_obj, mp_obj_t elempack_obj, mp_obj_t allocator_obj) {
    int w = mp_obj_get_int(w_obj);
    int h = mp_obj_get_int(h_obj);
    size_t elemsize = (size_t)mp_obj_get_int(elemsize_obj);
    int elempack = mp_obj_get_int(elempack_obj);
    ncnn_allocator_t allocator = (ncnn_allocator_t)mp_obj_get_int(allocator_obj);
    ncnn_mat_t mat = ncnn_mat_create_2d_elem(w, h, elemsize, elempack, allocator);
    if (!mat) {
        return mp_const_none;
    }
    return mp_obj_new_int_from_ptr(mat);
}
static MP_DEFINE_CONST_FUN_OBJ_5(ncnn_mp_mat_create_2d_elem_obj, ncnn_mp_mat_create_2d_elem);

// c_api:  ncnn_mat_t ncnn_mat_create_3d_elem(int w, int h, int c, size_t elemsize, int elempack, ncnn_allocator_t allocator);
// Python: ncnn_mp.mat_create_3d_elem(w, h, c, elemsize, elempack, allocator) -> int (handle)
static mp_obj_t ncnn_mp_mat_create_3d_elem(mp_obj_t w_obj, mp_obj_t h_obj, mp_obj_t c_obj, mp_obj_t elemsize_obj, mp_obj_t elempack_obj, mp_obj_t allocator_obj) {
    int w = mp_obj_get_int(w_obj);
    int h = mp_obj_get_int(h_obj);
    int c = mp_obj_get_int(c_obj);
    size_t elemsize = (size_t)mp_obj_get_int(elemsize_obj);
    int elempack = mp_obj_get_int(elempack_obj);
    ncnn_allocator_t allocator = (ncnn_allocator_t)mp_obj_get_int(allocator_obj);
    ncnn_mat_t mat = ncnn_mat_create_3d_elem(w, h, c, elemsize, elempack, allocator);
    if (!mat) {
        return mp_const_none;
    }
    return mp_obj_new_int_from_ptr(mat);
}
static MP_DEFINE_CONST_FUN_OBJ_6(ncnn_mp_mat_create_3d_elem_obj, ncnn_mp_mat_create_3d_elem);

// c_api:  ncnn_mat_t ncnn_mat_create_4d_elem(int w, int h, int d, int c, size_t elemsize, int elempack, ncnn_allocator_t allocator);
// Python: ncnn_mp.mat_create_4d_elem(w, h, d, c, elemsize, elempack, allocator) -> int (handle)
static mp_obj_t ncnn_mp_mat_create_4d_elem(mp_obj_t w_obj, mp_obj_t h_obj, mp_obj_t d_obj, mp_obj_t c_obj, mp_obj_t elemsize_obj, mp_obj_t elempack_obj, mp_obj_t allocator_obj) {
    int w = mp_obj_get_int(w_obj);
    int h = mp_obj_get_int(h_obj);
    int d = mp_obj_get_int(d_obj);
    int c = mp_obj_get_int(c_obj);
    size_t elemsize = (size_t)mp_obj_get_int(elemsize_obj);
    int elempack = mp_obj_get_int(elempack_obj);
    ncnn_allocator_t allocator = (ncnn_allocator_t)mp_obj_get_int(allocator_obj);
    ncnn_mat_t mat = ncnn_mat_create_4d_elem(w, h, d, c, elemsize, elempack, allocator);
    if (!mat) {
        return mp_const_none;
    }
    return mp_obj_new_int_from_ptr(mat);
}
static MP_DEFINE_CONST_FUN_OBJ_7(ncnn_mp_mat_create_4d_elem_obj, ncnn_mp_mat_create_4d_elem);

// c_api:  ncnn_mat_t ncnn_mat_create_external_1d_elem(int w, void* data, size_t elemsize, int elempack, ncnn_allocator_t allocator);
// Python: ncnn_mp.mat_create_external_1d_elem(w, data, elemsize, elempack, allocator) -> int (handle)
static mp_obj_t ncnn_mp_mat_create_external_1d_elem(mp_obj_t w_obj, mp_obj_t data_obj, mp_obj_t elemsize_obj, mp_obj_t elempack_obj, mp_obj_t allocator_obj) {
    int w = mp_obj_get_int(w_obj);
    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(data_obj, &bufinfo, MP_BUFFER_READ);
    size_t elemsize = (size_t)mp_obj_get_int(elemsize_obj);
    int elempack = mp_obj_get_int(elempack_obj);
    ncnn_allocator_t allocator = (ncnn_allocator_t)mp_obj_get_int(allocator_obj);
    ncnn_mat_t mat = ncnn_mat_create_external_1d_elem(w, bufinfo.buf, elemsize, elempack, allocator);
    if (!mat) {
        return mp_const_none;
    }
    return mp_obj_new_int_from_ptr(mat);
}
static MP_DEFINE_CONST_FUN_OBJ_5(ncnn_mp_mat_create_external_1d_elem_obj, ncnn_mp_mat_create_external_1d_elem);

// c_api:  ncnn_mat_t ncnn_mat_create_external_2d_elem(int w, int h, void* data, size_t elemsize, int elempack, ncnn_allocator_t allocator);
// Python: ncnn_mp.mat_create_external_2d_elem(w, h, data, elemsize, elempack, allocator) -> int (handle)
static mp_obj_t ncnn_mp_mat_create_external_2d_elem(mp_obj_t w_obj, mp_obj_t h_obj, mp_obj_t data_obj, mp_obj_t elemsize_obj, mp_obj_t elempack_obj, mp_obj_t allocator_obj) {
    int w = mp_obj_get_int(w_obj);
    int h = mp_obj_get_int(h_obj);
    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(data_obj, &bufinfo, MP_BUFFER_READ);
    size_t elemsize = (size_t)mp_obj_get_int(elemsize_obj);
    int elempack = mp_obj_get_int(elempack_obj);
    ncnn_allocator_t allocator = (ncnn_allocator_t)mp_obj_get_int(allocator_obj);
    ncnn_mat_t mat = ncnn_mat_create_external_2d_elem(w, h, bufinfo.buf, elemsize, elempack, allocator);
    if (!mat) {
        return mp_const_none;
    }
    return mp_obj_new_int_from_ptr(mat);
}
static MP_DEFINE_CONST_FUN_OBJ_6(ncnn_mp_mat_create_external_2d_elem_obj, ncnn_mp_mat_create_external_2d_elem);

// c_api:  ncnn_mat_t ncnn_mat_create_external_3d_elem(int w, int h, int c, void* data, size_t elemsize, int elempack, ncnn_allocator_t allocator);
// Python: ncnn_mp.mat_create_external_3d_elem(w, h, c, data, elemsize, elempack, allocator) -> int (handle)
static mp_obj_t ncnn_mp_mat_create_external_3d_elem(mp_obj_t w_obj, mp_obj_t h_obj, mp_obj_t c_obj, mp_obj_t data_obj, mp_obj_t elemsize_obj, mp_obj_t elempack_obj, mp_obj_t allocator_obj) {
    int w = mp_obj_get_int(w_obj);
    int h = mp_obj_get_int(h_obj);
    int c = mp_obj_get_int(c_obj);
    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(data_obj, &bufinfo, MP_BUFFER_READ);
    size_t elemsize = (size_t)mp_obj_get_int(elemsize_obj);
    int elempack = mp_obj_get_int(elempack_obj);
    ncnn_allocator_t allocator = (ncnn_allocator_t)mp_obj_get_int(allocator_obj);
    ncnn_mat_t mat = ncnn_mat_create_external_3d_elem(w, h, c, bufinfo.buf, elemsize, elempack, allocator);
    if (!mat) {
        return mp_const_none;
    }
    return mp_obj_new_int_from_ptr(mat);
}
static MP_DEFINE_CONST_FUN_OBJ_7(ncnn_mp_mat_create_external_3d_elem_obj, ncnn_mp_mat_create_external_3d_elem);

// c_api:  ncnn_mat_t ncnn_mat_create_external_4d_elem(int w, int h, int d, int c, void* data, size_t elemsize, int elempack, ncnn_allocator_t allocator);
// Python: ncnn_mp.mat_create_external_4d_elem(w, h, d, c, data, elemsize, elempack, allocator) -> int (handle)
static mp_obj_t ncnn_mp_mat_create_external_4d_elem(mp_obj_t w_obj, mp_obj_t h_obj, mp_obj_t d_obj, mp_obj_t c_obj, mp_obj_t data_obj, mp_obj_t elemsize_obj, mp_obj_t elempack_obj, mp_obj_t allocator_obj) {
    int w = mp_obj_get_int(w_obj);
    int h = mp_obj_get_int(h_obj);
    int d = mp_obj_get_int(d_obj);
    int c = mp_obj_get_int(c_obj);
    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(data_obj, &bufinfo, MP_BUFFER_READ);
    size_t elemsize = (size_t)mp_obj_get_int(elemsize_obj);
    int elempack = mp_obj_get_int(elempack_obj);
    ncnn_allocator_t allocator = (ncnn_allocator_t)mp_obj_get_int(allocator_obj);
    ncnn_mat_t mat = ncnn_mat_create_external_4d_elem(w, h, d, c, bufinfo.buf, elemsize, elempack, allocator);
    if (!mat) {
        return mp_const_none;
    }
    return mp_obj_new_int_from_ptr(mat);
}
static MP_DEFINE_CONST_FUN_OBJ_8(ncnn_mp_mat_create_external_4d_elem_obj, ncnn_mp_mat_create_external_4d_elem);

// c_api:  void ncnn_mat_destroy(ncnn_mat_t mat);
// Python: ncnn_mp.mat_destroy(mat_handle)
static mp_obj_t ncnn_mp_mat_destroy(mp_obj_t mat_obj) {
    ncnn_mat_t mat = (ncnn_mat_t)mp_obj_get_int(mat_obj);
    if (mat) {
        ncnn_mat_destroy(mat);
    }
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_1(ncnn_mp_mat_destroy_obj, ncnn_mp_mat_destroy);

// c_api:  void ncnn_mat_fill_float(ncnn_mat_t mat, float v);
// Python: ncnn_mp.mat_fill_float(mat_handle, value)
static mp_obj_t ncnn_mp_mat_fill_float(mp_obj_t mat_obj, mp_obj_t value_obj) {
    ncnn_mat_t mat = (ncnn_mat_t)mp_obj_get_int(mat_obj);
    float value = mp_obj_get_float(value_obj);
    ncnn_mat_fill_float(mat, value);
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_2(ncnn_mp_mat_fill_float_obj, ncnn_mp_mat_fill_float);

// c_api:  ncnn_mat_t ncnn_mat_clone(const ncnn_mat_t mat, ncnn_allocator_t allocator);
// Python: ncnn_mp.mat_clone(mat_handle, allocator) -> int (handle)
static mp_obj_t ncnn_mp_mat_clone(mp_obj_t mat_obj) {
    ncnn_mat_t mat = (ncnn_mat_t)mp_obj_get_int(mat_obj);
    ncnn_allocator_t allocator = (ncnn_allocator_t)mp_obj_get_int(allocator_obj);
    ncnn_mat_t cloned_mat = ncnn_mat_clone(mat, allocator);
    if (!cloned_mat) {
        return mp_const_none;
    }
    return mp_obj_new_int_from_ptr(cloned_mat);
}
static MP_DEFINE_CONST_FUN_OBJ_1(ncnn_mp_mat_clone_obj, ncnn_mp_mat_clone);

// c_api:  ncnn_mat_t ncnn_mat_reshape_1d(const ncnn_mat_t mat, int w, ncnn_allocator_t allocator);
// Python: ncnn_mp.mat_reshape_1d(mat_handle, w, allocator) -> int (handle)
static mp_obj_t ncnn_mp_mat_reshape_1d(mp_obj_t mat_obj, mp_obj_t w_obj, mp_obj_t allocator_obj) {
    ncnn_mat_t mat = (ncnn_mat_t)mp_obj_get_int(mat_obj);
    int w = mp_obj_get_int(w_obj);
    ncnn_allocator_t allocator = (ncnn_allocator_t)mp_obj_get_int(allocator_obj);
    ncnn_mat_t reshaped_mat = ncnn_mat_reshape_1d(mat, w, allocator);
    if (!reshaped_mat) {
        return mp_const_none;
    }
    return mp_obj_new_int_from_ptr(reshaped_mat);
}
static MP_DEFINE_CONST_FUN_OBJ_3(ncnn_mp_mat_reshape_1d_obj, ncnn_mp_mat_reshape_1d);

// c_api:  ncnn_mat_t ncnn_mat_reshape_2d(const ncnn_mat_t mat, int w, int h, ncnn_allocator_t allocator);
// Python: ncnn_mp.mat_reshape_2d(mat_handle, w, h, allocator) -> int (handle)
static mp_obj_t ncnn_mp_mat_reshape_2d(mp_obj_t mat_obj, mp_obj_t w_obj, mp_obj_t h_obj, mp_obj_t allocator_obj) {
    ncnn_mat_t mat = (ncnn_mat_t)mp_obj_get_int(mat_obj);
    int w = mp_obj_get_int(w_obj);
    int h = mp_obj_get_int(h_obj);
    ncnn_allocator_t allocator = (ncnn_allocator_t)mp_obj_get_int(allocator_obj);
    ncnn_mat_t reshaped_mat = ncnn_mat_reshape_2d(mat, w, h, allocator);
    if (!reshaped_mat) {
        return mp_const_none;
    }
    return mp_obj_new_int_from_ptr(reshaped_mat);
}
static MP_DEFINE_CONST_FUN_OBJ_4(ncnn_mp_mat_reshape_2d_obj, ncnn_mp_mat_reshape_2d);

// c_api:  ncnn_mat_t ncnn_mat_reshape_3d(const ncnn_mat_t mat, int w, int h, int c, ncnn_allocator_t allocator);
// Python: ncnn_mp.mat_reshape_3d(mat_handle, w, h, c, allocator) -> int (handle)
static mp_obj_t ncnn_mp_mat_reshape_3d(mp_obj_t mat_obj, mp_obj_t w_obj, mp_obj_t h_obj, mp_obj_t c_obj, mp_obj_t allocator_obj) {
    ncnn_mat_t mat = (ncnn_mat_t)mp_obj_get_int(mat_obj);
    int w = mp_obj_get_int(w_obj);
    int h = mp_obj_get_int(h_obj);
    int c = mp_obj_get_int(c_obj);
    ncnn_allocator_t allocator = (ncnn_allocator_t)mp_obj_get_int(allocator_obj);
    ncnn_mat_t reshaped_mat = ncnn_mat_reshape_3d(mat, w, h, c, allocator);
    if (!reshaped_mat) {
        return mp_const_none;
    }
    return mp_obj_new_int_from_ptr(reshaped_mat);
}
static MP_DEFINE_CONST_FUN_OBJ_5(ncnn_mp_mat_reshape_3d_obj, ncnn_mp_mat_reshape_3d);

// c_api:  ncnn_mat_t ncnn_mat_reshape_4d(const ncnn_mat_t mat, int w, int h, int c, ncnn_allocator_t allocator);
// Python: ncnn_mp.mat_reshape_4d(mat_handle, w, h, c, allocator) -> int (handle)
static mp_obj_t ncnn_mp_mat_reshape_4d(mp_obj_t mat_obj, mp_obj_t w_obj, mp_obj_t h_obj, mp_obj_t d_obj, mp_obj_t c_obj, mp_obj_t allocator_obj) {
    ncnn_mat_t mat = (ncnn_mat_t)mp_obj_get_int(mat_obj);
    int w = mp_obj_get_int(w_obj);
    int h = mp_obj_get_int(h_obj);
    int d = mp_obj_get_int(d_obj);
    int c = mp_obj_get_int(c_obj);
    ncnn_allocator_t allocator = (ncnn_allocator_t)mp_obj_get_int(allocator_obj);
    ncnn_mat_t reshaped_mat = ncnn_mat_reshape_4d(mat, w, h, d, c, allocator);
    if (!reshaped_mat) {
        return mp_const_none;
    }
    return mp_obj_new_int_from_ptr(reshaped_mat);
}
static MP_DEFINE_CONST_FUN_OBJ_6(ncnn_mp_mat_reshape_4d_obj, ncnn_mp_mat_reshape_4d);

// c_api:  int ncnn_mat_get_dims(const ncnn_mat_t mat);
// Python: ncnn_mp.mat_get_dims(mat_handle) -> int
static mp_obj_t ncnn_mp_mat_get_dims(mp_obj_t mat_obj) {
    ncnn_mat_t mat = (ncnn_mat_t)mp_obj_get_int(mat_obj);
    int dims = ncnn_mat_get_dims(mat);
    return mp_obj_new_int(dims);
}
static MP_DEFINE_CONST_FUN_OBJ_1(ncnn_mp_mat_get_dims_obj, ncnn_mp_mat_get_dims);

// c_api:  int ncnn_mat_get_X(const ncnn_mat_t mat); (w, h, d, c)
// Python: ncnn_mp.mat_get_X(mat_handle) -> int
static mp_obj_t ncnn_mp_mat_get_w(mp_obj_t mat_obj) {
    return mp_obj_new_int(ncnn_mat_get_w((ncnn_mat_t)mp_obj_get_int(mat_obj)));
}
static MP_DEFINE_CONST_FUN_OBJ_1(ncnn_mp_mat_get_w_obj, ncnn_mp_mat_get_w);

static mp_obj_t ncnn_mp_mat_get_h(mp_obj_t mat_obj) {
    return mp_obj_new_int(ncnn_mat_get_h((ncnn_mat_t)mp_obj_get_int(mat_obj)));
}
static MP_DEFINE_CONST_FUN_OBJ_1(ncnn_mp_mat_get_h_obj, ncnn_mp_mat_get_h);

static mp_obj_t ncnn_mp_mat_get_d(mp_obj_t mat_obj) {
    return mp_obj_new_int(ncnn_mat_get_d((ncnn_mat_t)mp_obj_get_int(mat_obj)));
}
static MP_DEFINE_CONST_FUN_OBJ_1(ncnn_mp_mat_get_d_obj, ncnn_mp_mat_get_d);

static mp_obj_t ncnn_mp_mat_get_c(mp_obj_t mat_obj) {
    return mp_obj_new_int(ncnn_mat_get_c((ncnn_mat_t)mp_obj_get_int(mat_obj)));
}
static MP_DEFINE_CONST_FUN_OBJ_1(ncnn_mp_mat_get_c_obj, ncnn_mp_mat_get_c);

// c_api:  size_t ncnn_mat_get_elemsize(const ncnn_mat_t mat);
// Python: ncnn_mp.mat_get_elemsize(mat_handle) -> int
static mp_obj_t ncnn_mp_mat_get_elemsize(mp_obj_t mat_obj) {
    ncnn_mat_t mat = (ncnn_mat_t)mp_obj_get_int(mat_obj);
    size_t elemsize = ncnn_mat_get_elemsize(mat);
    return mp_obj_new_int(elemsize);
}
static MP_DEFINE_CONST_FUN_OBJ_1(ncnn_mp_mat_get_elemsize_obj, ncnn_mp_mat_get_elemsize);

// c_api:  int ncnn_mat_get_elempack(const ncnn_mat_t mat);
// Python: ncnn_mp.mat_get_elempack(mat_handle) -> int
static mp_obj_t ncnn_mp_mat_get_elempack(mp_obj_t mat_obj) {
    ncnn_mat_t mat = (ncnn_mat_t)mp_obj_get_int(mat_obj);
    int elempack = ncnn_mat_get_elempack(mat);
    return mp_obj_new_int(elempack);
}
static MP_DEFINE_CONST_FUN_OBJ_1(ncnn_mp_mat_get_elempack_obj, ncnn_mp_mat_get_elempack);

// c_api:  size_t ncnn_mat_get_cstep(const ncnn_mat_t mat);
// Python: ncnn_mp.mat_get_cstep(mat_handle) -> int
static mp_obj_t ncnn_mp_mat_get_cstep(mp_obj_t mat_obj) {
    ncnn_mat_t mat = (ncnn_mat_t)mp_obj_get_int(mat_obj);
    size_t cstep = ncnn_mat_get_cstep(mat);
    return mp_obj_new_int(cstep);
}
static MP_DEFINE_CONST_FUN_OBJ_1(ncnn_mp_mat_get_cstep_obj, ncnn_mp_mat_get_cstep);

// c_api:  void* ncnn_mat_get_data(const ncnn_mat_t mat);
// Python: ncnn_mp.mat_get_data_ptr(mat_handle) -> int (pointer as int)
static mp_obj_t ncnn_mp_mat_get_data_ptr(mp_obj_t mat_obj) {
    ncnn_mat_t mat = (ncnn_mat_t)mp_obj_get_int(mat_obj);
    void* data_ptr = ncnn_mat_get_data(mat);
    return mp_obj_new_int_from_ptr(data_ptr);
}
static MP_DEFINE_CONST_FUN_OBJ_1(ncnn_mp_mat_get_data_ptr_obj, ncnn_mp_mat_get_data_ptr);

// c_api:  void* ncnn_mat_get_channel_data(const ncnn_mat_t mat, int c);
// Python: ncnn_mp.mat_get_channel_data(mat_handle, channel) -> int (pointer as int)
static mp_obj_t ncnn_mp_mat_get_channel_data(mp_obj_t mat_obj, mp_obj_t channel_obj) {
    ncnn_mat_t mat = (ncnn_mat_t)mp_obj_get_int(mat_obj);
    int channel = mp_obj_get_int(channel_obj);
    void* channel_data_ptr = ncnn_mat_get_channel_data(mat, channel);
    return mp_obj_new_int_from_ptr(channel_data_ptr);
}
static MP_DEFINE_CONST_FUN_OBJ_2(ncnn_mp_mat_get_channel_data_obj, ncnn_mp_mat_get_channel_data);


// ------------------
/* mat pixel api */
// ------------------
// c_api:  ncnn_mat_t ncnn_mat_from_pixels(const unsigned char* pixels, int type, int w, int h, int stride, ncnn_allocator_t allocator);
// Python: ncnn_mp.mat_from_pixels(pixel_bytes, type, w, h, stride, allocator) -> int (handle)
static mp_obj_t ncnn_mp_mat_from_pixels(size_t n_args, const mp_obj_t *args) {
    mp_arg_check_num(n_args, 0, 6, 6, false);

    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(args[0], &bufinfo, MP_BUFFER_READ);
    
    int type = mp_obj_get_int(args[1]);
    int w = mp_obj_get_int(args[2]);
    int h = mp_obj_get_int(args[3]);
    int stride = mp_obj_get_int(args[4]);
    ncnn_allocator_t allocator = (ncnn_allocator_t)mp_obj_get_int(args[5]);
    
    ncnn_mat_t mat = ncnn_mat_from_pixels((const unsigned char*)bufinfo.buf, type, w, h, stride, allocator);
    
    if (!mat) {
        return mp_const_none;
    }
    return mp_obj_new_int_from_ptr(mat);
}
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(ncnn_mp_mat_from_pixels_obj, 6, 6, ncnn_mp_mat_from_pixels);

// c_api:  ncnn_mat_t ncnn_mat_from_pixels_resize(const unsigned char* pixels, int type, int w, int h, int stride, int target_width, int target_height, ncnn_allocator_t allocator);
// Python: ncnn_mp.mat_from_pixels_resize(pixel_bytes, type, w, h, stride, target_w, target_h, allocator) -> int (handle)
static mp_obj_t ncnn_mp_mat_from_pixels_resize(size_t n_args, const mp_obj_t *args) {
    mp_arg_check_num(n_args, 0, 8, 8, false);

    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(args[0], &bufinfo, MP_BUFFER_READ);
    
    int type = mp_obj_get_int(args[1]);
    int w = mp_obj_get_int(args[2]);
    int h = mp_obj_get_int(args[3]);
    int stride = mp_obj_get_int(args[4]);
    int target_width = mp_obj_get_int(args[5]);
    int target_height = mp_obj_get_int(args[6]);
    ncnn_allocator_t allocator = (ncnn_allocator_t)mp_obj_get_int(args[7]);

    ncnn_mat_t mat = ncnn_mat_from_pixels_resize((const unsigned char*)bufinfo.buf, type, w, h, stride, target_width, target_height, allocator);
    
    if (!mat) {
        return mp_const_none;
    }
    return mp_obj_new_int_from_ptr(mat);
}
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(ncnn_mp_mat_from_pixels_resize_obj, 8, 8, ncnn_mp_mat_from_pixels_resize);

// c_api:  ncnn_mat_t ncnn_mat_from_pixels_roi(const unsigned char* pixels, int type, int w, int h, int stride, int roix, int roiy, int roiw, int roih, ncnn_allocator_t allocator);
// Python: ncnn_mp.mat_from_pixels_roi(pixel_bytes, type, w, h, stride, roix, roiy, roiw, roih, allocator) -> int (handle)
static mp_obj_t ncnn_mp_mat_from_pixels_roi(size_t n_args, const mp_obj_t *args) {
    mp_arg_check_num(n_args, 0, 10, 10, false);

    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(args[0], &bufinfo, MP_BUFFER_READ);
    
    int type = mp_obj_get_int(args[1]);
    int w = mp_obj_get_int(args[2]);
    int h = mp_obj_get_int(args[3]);
    int stride = mp_obj_get_int(args[4]);
    int roix = mp_obj_get_int(args[5]);
    int roiy = mp_obj_get_int(args[6]);
    int roiw = mp_obj_get_int(args[7]);
    int roih = mp_obj_get_int(args[8]);
    ncnn_allocator_t allocator = (ncnn_allocator_t)mp_obj_get_int(args[9]);

    ncnn_mat_t mat = ncnn_mat_from_pixels_roi((const unsigned char*)bufinfo.buf, type, w, h, stride, roix, roiy, roiw, roih, allocator);
    
    if (!mat) {
        return mp_const_none;
    }
    return mp_obj_new_int_from_ptr(mat);
}
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(ncnn_mp_mat_from_pixels_roi_obj, 10, 10, ncnn_mp_mat_from_pixels_roi);

// c_api:  ncnn_mat_t ncnn_mat_from_pixels_roi_resize(const unsigned char* pixels, int type, int w, int h, int stride, int roix, int roiy, int roiw, int roih, int target_width, int target_height, ncnn_allocator_t allocator);
// Python: ncnn_mp.mat_from_pixels_roi_resize(pixel_bytes, type, w, h, stride, roix, roiy, roiw, roih, target_w, target_h, allocator) -> int (handle)
static mp_obj_t ncnn_mp_mat_from_pixels_roi_resize(size_t n_args, const mp_obj_t *args) {
    mp_arg_check_num(n_args, 0, 12, 12, false);

    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(args[0], &bufinfo, MP_BUFFER_READ);
    
    int type = mp_obj_get_int(args[1]);
    int w = mp_obj_get_int(args[2]);
    int h = mp_obj_get_int(args[3]);
    int stride = mp_obj_get_int(args[4]);
    int roix = mp_obj_get_int(args[5]);
    int roiy = mp_obj_get_int(args[6]);
    int roiw = mp_obj_get_int(args[7]);
    int roih = mp_obj_get_int(args[8]);
    int target_width = mp_obj_get_int(args[9]);
    int target_height = mp_obj_get_int(args[10]);
    ncnn_allocator_t allocator = (ncnn_allocator_t)mp_obj_get_int(args[11]);

    ncnn_mat_t mat = ncnn_mat_from_pixels_roi_resize((const unsigned char*)bufinfo.buf, type, w, h, stride, roix, roiy, roiw, roih, target_width, target_height, allocator);
    
    if (!mat) {
        return mp_const_none;
    }
    return mp_obj_new_int_from_ptr(mat);
}
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(ncnn_mp_mat_from_pixels_roi_resize_obj, 12, 12, ncnn_mp_mat_from_pixels_roi_resize);

// c_api:  void ncnn_mat_to_pixels(const ncnn_mat_t mat, unsigned char* pixels, int type, int stride);
// Python: ncnn_mp.mat_to_pixels(mat_handle, buffer, type, stride) -> None
static mp_obj_t ncnn_mp_mat_to_pixels(mp_obj_t mat_obj, mp_obj_t buffer_obj, mp_obj_t type_obj, mp_obj_t stride_obj) {
    ncnn_mat_t mat = (ncnn_mat_t)mp_obj_get_int(mat_obj);
    int type = mp_obj_get_int(type_obj);
    int stride = mp_obj_get_int(stride_obj);

    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(buffer_obj, &bufinfo, MP_BUFFER_WRITE);

    ncnn_mat_to_pixels(mat, (unsigned char*)bufinfo.buf, type, stride);
    
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_4(ncnn_mp_mat_to_pixels_obj, ncnn_mp_mat_to_pixels);

// c_api:  void ncnn_mat_to_pixels_resize(const ncnn_mat_t mat, unsigned char* pixels, int type, int target_width, int target_height, int target_stride);
// Python: ncnn_mp.mat_to_pixels_resize(mat_handle, buffer, type, target_w, target_h, target_stride) -> None
static mp_obj_t ncnn_mp_mat_to_pixels_resize(size_t n_args, const mp_obj_t *args) {
    mp_arg_check_num(n_args, 0, 6, 6, false);
    ncnn_mat_t mat = (ncnn_mat_t)mp_obj_get_int(args[0]);
    
    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(args[1], &bufinfo, MP_BUFFER_WRITE);

    int type = mp_obj_get_int(args[2]);
    int target_width = mp_obj_get_int(args[3]);
    int target_height = mp_obj_get_int(args[4]);
    int target_stride = mp_obj_get_int(args[5]);

    ncnn_mat_to_pixels_resize(mat, (unsigned char*)bufinfo.buf, type, target_width, target_height, target_stride);
    
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(ncnn_mp_mat_to_pixels_resize_obj, 6, 6, ncnn_mp_mat_to_pixels_resize);

// c_api:  void ncnn_mat_substract_mean_normalize(ncnn_mat_t mat, const float* mean_vals, const float* norm_vals);
// Python: ncnn_mp.mat_substract_mean_normalize(mat_handle, mean_buffer, norm_buffer) -> None
static mp_obj_t ncnn_mp_mat_substract_mean_normalize(mp_obj_t mat_obj, mp_obj_t mean_obj, mp_obj_t norm_obj) {
    ncnn_mat_t mat = (ncnn_mat_t)mp_obj_get_int(mat_obj);

    mp_buffer_info_t mean_buf;
    mp_get_buffer_raise(mean_obj, &mean_buf, MP_BUFFER_READ);
    mp_buffer_info_t norm_buf;
    mp_get_buffer_raise(norm_obj, &norm_buf, MP_BUFFER_READ);
    
    ncnn_mat_substract_mean_normalize(mat, (const float*)mean_buf.buf, (const float*)norm_buf.buf);

    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_3(ncnn_mp_mat_substract_mean_normalize_obj, ncnn_mp_mat_substract_mean_normalize);

// c_api:  void ncnn_convert_packing(const ncnn_mat_t src, ncnn_mat_t* dst, int elempack, const ncnn_option_t opt);
// Python: ncnn_mp.convert_packing(src_handle, dst_handle, elempack, opt_handle) -> None
static mp_obj_t ncnn_mp_convert_packing(mp_obj_t src_obj, mp_obj_t dst_obj, mp_obj_t elempack_obj, mp_obj_t opt_obj) {
    ncnn_mat_t src = (ncnn_mat_t)mp_obj_get_int(src_obj);
    ncnn_mat_t dst = (ncnn_mat_t)mp_obj_get_int(dst_obj);
    int elempack = mp_obj_get_int(elempack_obj);
    ncnn_option_t opt = (ncnn_option_t)mp_obj_get_int(opt_obj);
    ncnn_convert_packing(src, &dst, elempack, opt);
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_4(ncnn_mp_convert_packing_obj, ncnn_mp_convert_packing);

// c_api:  void ncnn_flatten(const ncnn_mat_t src, ncnn_mat_t* dst, const ncnn_option_t opt);
// Python: ncnn_mp.flatten(src_handle, dst_handle, opt_handle) -> None
static mp_obj_t ncnn_mp_flatten(mp_obj_t src_obj, mp_obj_t dst_obj, mp_obj_t opt_obj) {
    ncnn_mat_t   src = (ncnn_mat_t)mp_obj_get_int(src_obj);
    ncnn_mat_t   dst = (ncnn_mat_t)mp_obj_get_int(dst_obj);
    ncnn_option_t opt = (ncnn_option_t)mp_obj_get_int(opt_obj);
    ncnn_flatten(src, &dst, opt);
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_3(ncnn_mp_flatten_obj, ncnn_mp_flatten);
