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

// ------------------
/* blob api */
// ------------------
#if NCNN_STRING
// c_api:  const char* ncnn_blob_get_name(const ncnn_blob_t blob);
// Python: ncnn_mp.blob_get_name(blob_handle) -> str
static mp_obj_t ncnn_mp_blob_get_name(mp_obj_t blob_obj) {
    ncnn_blob_t blob = (ncnn_blob_t)mp_obj_get_int(blob_obj);
    const char* name = ncnn_blob_get_name(blob);
    return mp_obj_new_str(name, strlen(name));
}
static MP_DEFINE_CONST_FUN_OBJ_1(ncnn_mp_blob_get_name_obj, ncnn_mp_blob_get_name);
#endif // NCNN_STRING

// c_api:  int ncnn_blob_get_producer(const ncnn_blob_t blob);
// Python: ncnn_mp.blob_get_producer(blob_handle) -> int
static mp_obj_t ncnn_mp_blob_get_producer(mp_obj_t blob_obj) {
    ncnn_blob_t blob = (ncnn_blob_t)mp_obj_get_int(blob_obj);
    int producer = ncnn_blob_get_producer(blob);
    return mp_obj_new_int(producer);
}
static MP_DEFINE_CONST_FUN_OBJ_1(ncnn_mp_blob_get_producer_obj, ncnn_mp_blob_get_producer);

// c_api:  int ncnn_blob_get_consumer(const ncnn_blob_t blob);
// Python: ncnn_mp.blob_get_consumer(blob_handle) -> int
static mp_obj_t ncnn_mp_blob_get_consumer(mp_obj_t blob_obj) {
    ncnn_blob_t blob = (ncnn_blob_t)mp_obj_get_int(blob_obj);
    int consumer = ncnn_blob_get_consumer(blob);
    return mp_obj_new_int(consumer);
}
static MP_DEFINE_CONST_FUN_OBJ_1(ncnn_mp_blob_get_consumer_obj, ncnn_mp_blob_get_consumer);

// TODO: fix some return void func.
// c_api:  void ncnn_blob_get_shape(const ncnn_blob_t blob, int* dims, int* w, int* h, int* c);
// Python: ncnn_mp.blob_get_shape(blob_handle) -> tuple (dims, w, h, c)
static mp_obj_t ncnn_mp_blob_get_shape(mp_obj_t blob_obj) {
    ncnn_blob_t blob = (ncnn_blob_t)mp_obj_get_int(blob_obj);
    
    int dims, w, h, c;
    ncnn_blob_get_shape(blob, &dims, &w, &h, &c);
    
    mp_obj_t items[] = {
        mp_obj_new_int(dims),
        mp_obj_new_int(w),
        mp_obj_new_int(h),
        mp_obj_new_int(c),
    };
    
    return mp_obj_new_tuple(4, items);
}
static MP_DEFINE_CONST_FUN_OBJ_1(ncnn_mp_blob_get_shape_obj, ncnn_mp_blob_get_shape);


// ------------------
/* paramdict api */
// ------------------
// c_api:  ncnn_paramdict_t ncnn_paramdict_create(void);
// Python: ncnn_mp.paramdict_create() -> int (handle)
static mp_obj_t ncnn_mp_paramdict_create(void) {
    ncnn_paramdict_t paramdict = ncnn_paramdict_create();
    return mp_obj_new_int_from_ptr(paramdict);
}
static MP_DEFINE_CONST_FUN_OBJ_0(ncnn_mp_paramdict_create_obj, ncnn_mp_paramdict_create);

// c_api:  void ncnn_paramdict_destroy(ncnn_paramdict_t pd);
// Python: ncnn_mp.paramdict_destroy(pd_handle) -> None
static mp_obj_t ncnn_mp_paramdict_destroy(mp_obj_t pd_obj) {
    ncnn_paramdict_t pd = (ncnn_paramdict_t)mp_obj_get_int(pd_obj);
    if (pd) {
        ncnn_paramdict_destroy(pd);
    }
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_1(ncnn_mp_paramdict_destroy_obj, ncnn_mp_paramdict_destroy);

// c_api:  int ncnn_paramdict_get_type(const ncnn_paramdict_t pd, int id);
// Python: ncnn_mp.paramdict_get_type(pd_handle, id) -> int
static mp_obj_t ncnn_mp_paramdict_get_type(mp_obj_t pd_obj, mp_obj_t id_obj) {
    ncnn_paramdict_t pd = (ncnn_paramdict_t)mp_obj_get_int(pd_obj);
    int id = mp_obj_get_int(id_obj);
    int type = ncnn_paramdict_get_type(pd, id);
    return mp_obj_new_int(type);
}
static MP_DEFINE_CONST_FUN_OBJ_2(ncnn_mp_paramdict_get_type_obj, ncnn_mp_paramdict_get_type);

// c_api:  int ncnn_paramdict_get_int(const ncnn_paramdict_t pd, int id, int def);
// Python: ncnn_mp.paramdict_get_int(pd_handle, id, def) -> int
static mp_obj_t ncnn_mp_paramdict_get_int(mp_obj_t pd_obj, mp_obj_t id_obj, mp_obj_t def_obj) {
    ncnn_paramdict_t pd = (ncnn_paramdict_t)mp_obj_get_int(pd_obj);
    int id = mp_obj_get_int(id_obj);
    int def = mp_obj_get_int(def_obj);
    int result = ncnn_paramdict_get_int(pd, id, def);
    return mp_obj_new_int(result);
}
static MP_DEFINE_CONST_FUN_OBJ_3(ncnn_mp_paramdict_get_int_obj, ncnn_mp_paramdict_get_int);

// c_api:  float ncnn_paramdict_get_float(const ncnn_paramdict_t pd, int id, float def);
// Python: ncnn_mp.paramdict_get_float(pd_handle, id, def) -> float
static mp_obj_t ncnn_mp_paramdict_get_float(mp_obj_t pd_obj, mp_obj_t id_obj, mp_obj_t def_obj) {
    ncnn_paramdict_t pd = (ncnn_paramdict_t)mp_obj_get_int(pd_obj);
    int id = mp_obj_get_int(id_obj);
    float def = mp_obj_get_float(def_obj);
    float result = ncnn_paramdict_get_float(pd, id, def);
    return mp_obj_new_float(result);
}
static MP_DEFINE_CONST_FUN_OBJ_3(ncnn_mp_paramdict_get_float_obj, ncnn_mp_paramdict_get_float);

// c_api:  ncnn_mat_t ncnn_paramdict_get_array(ncnn_paramdict_t pd, int id, const ncnn_mat_t def);
// Python: ncnn_mp.paramdict_get_array(pd_handle, id, def_mat_handle) -> int (handle)
static mp_obj_t ncnn_mp_paramdict_get_array(mp_obj_t pd_obj, mp_obj_t id_obj, mp_obj_t def_obj) {
    ncnn_paramdict_t pd = (ncnn_paramdict_t)mp_obj_get_int(pd_obj);
    int id = mp_obj_get_int(id_obj);
    ncnn_mat_t def = (ncnn_mat_t)mp_obj_get_int(def_obj);
    ncnn_mat_t result = ncnn_paramdict_get_array(pd, id, def);
    if (!result) {
        return mp_const_none;
    }
    return mp_obj_new_int_from_ptr(result);
}
static MP_DEFINE_CONST_FUN_OBJ_3(ncnn_mp_paramdict_get_array_obj, ncnn_mp_paramdict_get_array);

// c_api:  void ncnn_paramdict_set_int(ncnn_paramdict_t pd, int id, int i);
// Python: ncnn_mp.paramdict_set_int(pd_handle, id, i) -> None
static mp_obj_t ncnn_mp_paramdict_set_int(mp_obj_t pd_obj, mp_obj_t id_obj, mp_obj_t i_obj) {
    ncnn_paramdict_t pd = (ncnn_paramdict_t)mp_obj_get_int(pd_obj);
    int id = mp_obj_get_int(id_obj);
    int i = mp_obj_get_int(i_obj);
    ncnn_paramdict_set_int(pd, id, i);
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_3(ncnn_mp_paramdict_set_int_obj, ncnn_mp_paramdict_set_int);

// c_api:  void ncnn_paramdict_set_float(ncnn_paramdict_t pd, int id, float f);
// Python: ncnn_mp.paramdict_set_float(pd_handle, id, f) -> None
static mp_obj_t ncnn_mp_paramdict_set_float(mp_obj_t pd_obj, mp_obj_t id_obj, mp_obj_t f_obj) {
    ncnn_paramdict_t pd = (ncnn_paramdict_t)mp_obj_get_int(pd_obj);
    int id = mp_obj_get_int(id_obj);
    float f = mp_obj_get_float(f_obj);
    ncnn_paramdict_set_float(pd, id, f);
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_3(ncnn_mp_paramdict_set_float_obj, ncnn_mp_paramdict_set_float);

// c_api:  void ncnn_paramdict_set_array(ncnn_paramdict_t pd, int id, ncnn_mat_t v);
// Python: ncnn_mp.paramdict_set_array(pd_handle, id, mat_handle) -> None
static mp_obj_t ncnn_mp_paramdict_set_array(mp_obj_t pd_obj, mp_obj_t id_obj, mp_obj_t v_obj) {
    ncnn_paramdict_t pd = (ncnn_paramdict_t)mp_obj_get_int(pd_obj);
    int id = mp_obj_get_int(id_obj);
    ncnn_mat_t v = (ncnn_mat_t)mp_obj_get_int(v_obj);
    ncnn_paramdict_set_array(pd, id, v);
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_3(ncnn_mp_paramdict_set_array_obj, ncnn_mp_paramdict_set_array);


// ------------------
/* datareader api */
// ------------------
// c_api:  ncnn_datareader_t ncnn_datareader_create(void);
// Python: ncnn_mp.datareader_create() -> int (handle)
static mp_obj_t ncnn_mp_datareader_create(void) {
    ncnn_datareader_t dr = ncnn_datareader_create();
    return mp_obj_new_int_from_ptr(dr);
}
static MP_DEFINE_CONST_FUN_OBJ_0(ncnn_mp_datareader_create_obj, ncnn_mp_datareader_create);

// TODO: ncnn_datareader_create_from_stdio

// c_api:  ncnn_datareader_t ncnn_datareader_create_from_memory(const unsigned char** mem);
// Python: ncnn_mp.datareader_create_from_memory(data_bytes) -> int (handle)
static mp_obj_t ncnn_mp_datareader_create_from_memory(mp_obj_t data_obj) {
    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(data_obj, &bufinfo, MP_BUFFER_READ);
    
    const unsigned char* mem_ptr = (const unsigned char*)bufinfo.buf;
    
    ncnn_datareader_t dr = ncnn_datareader_create_from_memory(&mem_ptr);
    if (!dr) {
        return mp_const_none;
    }
    return mp_obj_new_int_from_ptr(dr);
}
static MP_DEFINE_CONST_FUN_OBJ_1(ncnn_mp_datareader_create_from_memory_obj, ncnn_mp_datareader_create_from_memory);

// c_api:  void ncnn_datareader_destroy(ncnn_datareader_t dr);
// Python: ncnn_mp.datareader_destroy(dr_handle) -> None
static mp_obj_t ncnn_mp_datareader_destroy(mp_obj_t dr_obj) {
    ncnn_datareader_t dr = (ncnn_datareader_t)mp_obj_get_int(dr_obj);
    if (dr) {
        ncnn_datareader_destroy(dr);
    }
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_1(ncnn_mp_datareader_destroy_obj, ncnn_mp_datareader_destroy);


// ------------------
/* modelbin api */
// ------------------
// c_api:  ncnn_modelbin_t ncnn_modelbin_create_from_datareader(const ncnn_datareader_t dr);
// Python: ncnn_mp.modelbin_create_from_datareader(dr_handle) -> int (handle)
static mp_obj_t ncnn_mp_modelbin_create_from_datareader(mp_obj_t dr_obj) {
    ncnn_datareader_t dr = (ncnn_datareader_t)mp_obj_get_int(dr_obj);
    ncnn_modelbin_t mb = ncnn_modelbin_create_from_datareader(dr);
    if (!mb) {
        return mp_const_none;
    }
    return mp_obj_new_int_from_ptr(mb);
}
static MP_DEFINE_CONST_FUN_OBJ_1(ncnn_mp_modelbin_create_from_datareader_obj, ncnn_mp_modelbin_create_from_datareader);

// c_api:  ncnn_modelbin_t ncnn_modelbin_create_from_mat_array(const ncnn_mat_t* weights, int n);
// Python: ncnn_mp.modelbin_create_from_mat_array(list_of_mat_handles) -> int (handle)
static mp_obj_t ncnn_mp_modelbin_create_from_mat_array(mp_obj_t weights_list_obj) {
    mp_obj_t *items;
    size_t n;
    mp_obj_get_array(weights_list_obj, &n, &items);

    ncnn_mat_t* weights = m_new(ncnn_mat_t, n);
    for (size_t i = 0; i < n; i++) {
        weights[i] = (ncnn_mat_t)mp_obj_get_int(items[i]);
    }
    ncnn_modelbin_t mb = ncnn_modelbin_create_from_mat_array(weights, n);
    
    m_del(ncnn_mat_t, weights, n);

    if (!mb) {
        return mp_const_none;
    }
    return mp_obj_new_int_from_ptr(mb);
}
static MP_DEFINE_CONST_FUN_OBJ_1(ncnn_mp_modelbin_create_from_mat_array_obj, ncnn_mp_modelbin_create_from_mat_array);

// c_api:  void ncnn_modelbin_destroy(ncnn_modelbin_t mb);
// Python: ncnn_mp.modelbin_destroy(mb_handle) -> None
static mp_obj_t ncnn_mp_modelbin_destroy(mp_obj_t mb_obj) {
    ncnn_modelbin_t mb = (ncnn_modelbin_t)mp_obj_get_int(mb_obj);
    ncnn_modelbin_destroy(mb);
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_1(ncnn_mp_modelbin_destroy_obj, ncnn_mp_modelbin_destroy);


// ------------------
/* layer api */
// ------------------
// c_api:  ncnn_layer_t ncnn_layer_create(void);
// Python: ncnn_mp.layer_create() -> int (handle)
static mp_obj_t ncnn_mp_layer_create(void) {
    ncnn_layer_t layer = ncnn_layer_create();
    return mp_obj_new_int_from_ptr(layer);
}
static MP_DEFINE_CONST_FUN_OBJ_0(ncnn_mp_layer_create_obj, ncnn_mp_layer_create);

// c_api:  ncnn_layer_t ncnn_layer_create_by_typeindex(int typeindex);
// Python: ncnn_mp.layer_create_by_typeindex(typeindex) -> int (handle)
static mp_obj_t ncnn_mp_layer_create_by_typeindex(mp_obj_t typeindex_obj) {
    int typeindex = mp_obj_get_int(typeindex_obj);
    ncnn_layer_t layer = ncnn_layer_create_by_typeindex(typeindex);
    if (!layer) {
        return mp_const_none;
    }
    return mp_obj_new_int_from_ptr(layer);
}
static MP_DEFINE_CONST_FUN_OBJ_1(ncnn_mp_layer_create_by_typeindex_obj, ncnn_mp_layer_create_by_typeindex);

#if NCNN_STRING
// c_api:  ncnn_layer_t ncnn_layer_create_by_type(const char* type);
// Python: ncnn_mp.layer_create_by_type(type) -> int (handle)
static mp_obj_t ncnn_mp_layer_create_by_type(mp_obj_t type_obj) {
    const char* type = mp_obj_str_get_str(type_obj);
    ncnn_layer_t layer = ncnn_layer_create_by_type(type);
    if (!layer) {
        return mp_const_none;
    }
    return mp_obj_new_int_from_ptr(layer);
}
static MP_DEFINE_CONST_FUN_OBJ_1(ncnn_mp_layer_create_by_type_obj, ncnn_mp_layer_create_by_type);

// c_api:  int ncnn_layer_type_to_index(const char* type);
// Python: ncnn_mp.layer_type_to_index(type) -> int
static mp_obj_t ncnn_mp_layer_type_to_index(mp_obj_t type_obj) {
    const char* type = mp_obj_str_get_str(type_obj);
    int index = ncnn_layer_type_to_index(type);
    return mp_obj_new_int(index);
}
static MP_DEFINE_CONST_FUN_OBJ_1(ncnn_mp_layer_type_to_index_obj, ncnn_mp_layer_type_to_index);
#endif // NCNN_STRING

// c_api:  void ncnn_layer_destroy(ncnn_layer_t layer);
// Python: ncnn_mp.layer_destroy(layer_handle) -> None
static mp_obj_t ncnn_mp_layer_destroy(mp_obj_t layer_obj) {
    ncnn_layer_t layer = (ncnn_layer_t)mp_obj_get_int(layer_obj);
    ncnn_layer_destroy(layer);
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_1(ncnn_mp_layer_destroy_obj, ncnn_mp_layer_destroy);

#if NCNN_STRING
// c_api:  const char* ncnn_layer_get_name(const ncnn_layer_t layer);
// Python: ncnn_mp.layer_get_name(layer_handle) -> str
static mp_obj_t ncnn_mp_layer_get_name(mp_obj_t layer_obj) {
    ncnn_layer_t layer = (ncnn_layer_t)mp_obj_get_int(layer_obj);
    const char* name = ncnn_layer_get_name(layer);
    return mp_obj_new_str(name, strlen(name));
}
static MP_DEFINE_CONST_FUN_OBJ_1(ncnn_mp_layer_get_name_obj, ncnn_mp_layer_get_name);
#endif // NCNN_STRING

// c_api:  int ncnn_layer_get_typeindex(const ncnn_layer_t layer);
// Python: ncnn_mp.layer_get_typeindex(layer_handle) -> int
static mp_obj_t ncnn_mp_layer_get_typeindex(mp_obj_t layer_obj) {
    ncnn_layer_t layer = (ncnn_layer_t)mp_obj_get_int(layer_obj);
    int typeindex = ncnn_layer_get_typeindex(layer);
    return mp_obj_new_int(typeindex);
}
static MP_DEFINE_CONST_FUN_OBJ_1(ncnn_mp_layer_get_typeindex_obj, ncnn_mp_layer_get_typeindex);

#if NCNN_STRING
// c_api:  const char* ncnn_layer_get_type(const ncnn_layer_t layer);
// Python: ncnn_mp.layer_get_type(layer_handle) -> str
static mp_obj_t ncnn_mp_layer_get_type(mp_obj_t layer_obj) {
    ncnn_layer_t layer = (ncnn_layer_t)mp_obj_get_int(layer_obj);
    const char* type = ncnn_layer_get_type(layer);
    return mp_obj_new_str(type, strlen(type));
}
static MP_DEFINE_CONST_FUN_OBJ_1(ncnn_mp_layer_get_type_obj, ncnn_mp_layer_get_type);
#endif // NCNN_STRING

// c_api:  int ncnn_layer_get_one_blob_only(const ncnn_layer_t layer);
// Python: ncnn_mp.layer_get_one_blob_only(layer_handle) -> int
static mp_obj_t ncnn_mp_layer_get_one_blob_only(mp_obj_t layer_obj) {
    ncnn_layer_t layer = (ncnn_layer_t)mp_obj_get_int(layer_obj);
    int result = ncnn_layer_get_one_blob_only(layer);
    return mp_obj_new_int(result);
}
static MP_DEFINE_CONST_FUN_OBJ_1(ncnn_mp_layer_get_one_blob_only_obj, ncnn_mp_layer_get_one_blob_only);

// c_api:  int ncnn_layer_get_support_inplace(const ncnn_layer_t layer);
// Python: ncnn_mp.layer_get_support_inplace(layer_handle) -> int
static mp_obj_t ncnn_mp_layer_get_support_inplace(mp_obj_t layer_obj) {
    ncnn_layer_t layer = (ncnn_layer_t)mp_obj_get_int(layer_obj);
    int result = ncnn_layer_get_support_inplace(layer);
    return mp_obj_new_int(result);
}
static MP_DEFINE_CONST_FUN_OBJ_1(ncnn_mp_layer_get_support_inplace_obj, ncnn_mp_layer_get_support_inplace);

// c_api:  int ncnn_layer_get_support_vulkan(const ncnn_layer_t layer);
// Python: ncnn_mp.layer_get_support_vulkan(layer_handle) -> int
static mp_obj_t ncnn_mp_layer_get_support_vulkan(mp_obj_t layer_obj) {
    ncnn_layer_t layer = (ncnn_layer_t)mp_obj_get_int(layer_obj);
    int result = ncnn_layer_get_support_vulkan(layer);
    return mp_obj_new_int(result);
}
static MP_DEFINE_CONST_FUN_OBJ_1(ncnn_mp_layer_get_support_vulkan_obj, ncnn_mp_layer_get_support_vulkan);

// c_api:  int ncnn_layer_get_support_packing(const ncnn_layer_t layer);
// Python: ncnn_mp.layer_get_support_packing(layer_handle) -> int
static mp_obj_t ncnn_mp_layer_get_support_packing(mp_obj_t layer_obj) {
    ncnn_layer_t layer = (ncnn_layer_t)mp_obj_get_int(layer_obj);
    int result = ncnn_layer_get_support_packing(layer);
    return mp_obj_new_int(result);
}
static MP_DEFINE_CONST_FUN_OBJ_1(ncnn_mp_layer_get_support_packing_obj, ncnn_mp_layer_get_support_packing);

// c_api:  int ncnn_layer_get_support_bf16_storage(const ncnn_layer_t layer);
// Python: ncnn_mp.layer_get_support_bf16_storage(layer_handle) -> int
static mp_obj_t ncnn_mp_layer_get_support_bf16_storage(mp_obj_t layer_obj) {
    ncnn_layer_t layer = (ncnn_layer_t)mp_obj_get_int(layer_obj);
    int result = ncnn_layer_get_support_bf16_storage(layer);
    return mp_obj_new_int(result);
}
static MP_DEFINE_CONST_FUN_OBJ_1(ncnn_mp_layer_get_support_bf16_storage_obj, ncnn_mp_layer_get_support_bf16_storage);

// c_api:  int ncnn_layer_get_support_fp16_storage(const ncnn_layer_t layer);
// Python: ncnn_mp.layer_get_support_fp16_storage(layer_handle) -> int
static mp_obj_t ncnn_mp_layer_get_support_fp16_storage(mp_obj_t layer_obj) {
    ncnn_layer_t layer = (ncnn_layer_t)mp_obj_get_int(layer_obj);
    int result = ncnn_layer_get_support_fp16_storage(layer);
    return mp_obj_new_int(result);
}
static MP_DEFINE_CONST_FUN_OBJ_1(ncnn_mp_layer_get_support_fp16_storage_obj, ncnn_mp_layer_get_support_fp16_storage);

// c_api:  void ncnn_layer_set_one_blob_only(ncnn_layer_t layer, int enable);
// Python: ncnn_mp.layer_set_one_blob_only(layer_handle, enable) -> None
static mp_obj_t ncnn_mp_layer_set_one_blob_only(mp_obj_t layer_obj, mp_obj_t enable_obj) {
    ncnn_layer_t layer = (ncnn_layer_t)mp_obj_get_int(layer_obj);
    int enable = mp_obj_get_int(enable_obj);
    ncnn_layer_set_one_blob_only(layer, enable);
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_2(ncnn_mp_layer_set_one_blob_only_obj, ncnn_mp_layer_set_one_blob_only);

// c_api:  void ncnn_layer_set_support_inplace(ncnn_layer_t layer, int enable);
// Python: ncnn_mp.layer_set_support_inplace(layer_handle, enable) -> None
static mp_obj_t ncnn_mp_layer_set_support_inplace(mp_obj_t layer_obj, mp_obj_t enable_obj) {
    ncnn_layer_t layer = (ncnn_layer_t)mp_obj_get_int(layer_obj);
    int enable = mp_obj_get_int(enable_obj);
    ncnn_layer_set_support_inplace(layer, enable);
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_2(ncnn_mp_layer_set_support_inplace_obj, ncnn_mp_layer_set_support_inplace);

// c_api:  void ncnn_layer_set_support_vulkan(ncnn_layer_t layer, int enable);
// Python: ncnn_mp.layer_set_support_vulkan(layer_handle, enable) -> None
static mp_obj_t ncnn_mp_layer_set_support_vulkan(mp_obj_t layer_obj, mp_obj_t enable_obj) {
    ncnn_layer_t layer = (ncnn_layer_t)mp_obj_get_int(layer_obj);
    int enable = mp_obj_get_int(enable_obj);
    ncnn_layer_set_support_vulkan(layer, enable);
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_2(ncnn_mp_layer_set_support_vulkan_obj, ncnn_mp_layer_set_support_vulkan);

// c_api:  void ncnn_layer_set_support_packing(ncnn_layer_t layer, int enable);
// Python: ncnn_mp.layer_set_support_packing(layer_handle, enable) -> None
static mp_obj_t ncnn_mp_layer_set_support_packing(mp_obj_t layer_obj, mp_obj_t enable_obj) {
    ncnn_layer_t layer = (ncnn_layer_t)mp_obj_get_int(layer_obj);
    int enable = mp_obj_get_int(enable_obj);
    ncnn_layer_set_support_packing(layer, enable);
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_2(ncnn_mp_layer_set_support_packing_obj, ncnn_mp_layer_set_support_packing);

// c_api:  void ncnn_layer_set_support_bf16_storage(ncnn_layer_t layer, int enable);
// Python: ncnn_mp.layer_set_support_bf16_storage(layer_handle, enable) -> None
static mp_obj_t ncnn_mp_layer_set_support_bf16_storage(mp_obj_t layer_obj, mp_obj_t enable_obj) {
    ncnn_layer_t layer = (ncnn_layer_t)mp_obj_get_int(layer_obj);
    int enable = mp_obj_get_int(enable_obj);
    ncnn_layer_set_support_bf16_storage(layer, enable);
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_2(ncnn_mp_layer_set_support_bf16_storage_obj, ncnn_mp_layer_set_support_bf16_storage);

// c_api:  void ncnn_layer_set_support_fp16_storage(ncnn_layer_t layer, int enable);
// Python: ncnn_mp.layer_set_support_fp16_storage(layer_handle, enable) -> None
static mp_obj_t ncnn_mp_layer_set_support_fp16_storage(mp_obj_t layer_obj, mp_obj_t enable_obj) {
    ncnn_layer_t layer = (ncnn_layer_t)mp_obj_get_int(layer_obj);
    int enable = mp_obj_get_int(enable_obj);
    ncnn_layer_set_support_fp16_storage(layer, enable);
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_2(ncnn_mp_layer_set_support_fp16_storage_obj, ncnn_mp_layer_set_support_fp16_storage);

// c_api:  int ncnn_layer_get_bottom_count(const ncnn_layer_t layer);
// Python: ncnn_mp.layer_get_bottom_count(layer_handle) -> int
static mp_obj_t ncnn_mp_layer_get_bottom_count(mp_obj_t layer_obj) {
    ncnn_layer_t layer = (ncnn_layer_t)mp_obj_get_int(layer_obj);
    int count = ncnn_layer_get_bottom_count(layer);
    return mp_obj_new_int(count);
}
static MP_DEFINE_CONST_FUN_OBJ_1(ncnn_mp_layer_get_bottom_count_obj, ncnn_mp_layer_get_bottom_count);

// c_api:  int ncnn_layer_get_bottom(const ncnn_layer_t layer, int i);
// Python: ncnn_mp.layer_get_bottom(layer_handle, i) -> int
static mp_obj_t ncnn_mp_layer_get_bottom(mp_obj_t layer_obj, mp_obj_t i_obj) {
    ncnn_layer_t layer = (ncnn_layer_t)mp_obj_get_int(layer_obj);
    int i = mp_obj_get_int(i_obj);
    int bottom = ncnn_layer_get_bottom(layer, i);
    return mp_obj_new_int(bottom);
}
static MP_DEFINE_CONST_FUN_OBJ_2(ncnn_mp_layer_get_bottom_obj, ncnn_mp_layer_get_bottom);

// c_api:  int ncnn_layer_get_top_count(const ncnn_layer_t layer);
// Python: ncnn_mp.layer_get_top_count(layer_handle) -> int
static mp_obj_t ncnn_mp_layer_get_top_count(mp_obj_t layer_obj) {
    ncnn_layer_t layer = (ncnn_layer_t)mp_obj_get_int(layer_obj);
    int count = ncnn_layer_get_top_count(layer);
    return mp_obj_new_int(count);
}
static MP_DEFINE_CONST_FUN_OBJ_1(ncnn_mp_layer_get_top_count_obj, ncnn_mp_layer_get_top_count);

// c_api:  int ncnn_layer_get_top(const ncnn_layer_t layer, int i);
// Python: ncnn_mp.layer_get_top(layer_handle, i) -> int
static mp_obj_t ncnn_mp_layer_get_top(mp_obj_t layer_obj, mp_obj_t i_obj) {
    ncnn_layer_t layer = (ncnn_layer_t)mp_obj_get_int(layer_obj);
    int i = mp_obj_get_int(i_obj);
    int top = ncnn_layer_get_top(layer, i);
    return mp_obj_new_int(top);
}
static MP_DEFINE_CONST_FUN_OBJ_2(ncnn_mp_layer_get_top_obj, ncnn_mp_layer_get_top);

// c_api:  void ncnn_blob_get_bottom_shape(const ncnn_layer_t layer, int i, int* dims, int* w, int* h, int* c);
// Python: ncnn_mp.blob_get_bottom_shape(layer_handle, i) -> tuple
static mp_obj_t ncnn_mp_blob_get_bottom_shape(mp_obj_t layer_obj, mp_obj_t i_obj) {
    ncnn_layer_t layer = (ncnn_layer_t)mp_obj_get_int(layer_obj);
    int i = mp_obj_get_int(i_obj);

    int dims, w, h, c;
    ncnn_blob_get_bottom_shape(layer, i, &dims, &w, &h, &c);
    mp_obj_t items[] = {
        mp_obj_new_int(dims),
        mp_obj_new_int(w),
        mp_obj_new_int(h),
        mp_obj_new_int(c),
    };
    return mp_obj_new_tuple(4, items);
}
static MP_DEFINE_CONST_FUN_OBJ_2(ncnn_mp_blob_get_bottom_shape_obj, ncnn_mp_blob_get_bottom_shape);

// c_api:  void ncnn_blob_get_top_shape(const ncnn_layer_t layer, int i, int* dims, int* w, int* h, int* c);
// Python: ncnn_mp.blob_get_top_shape(layer_handle, i) -> tuple
static mp_obj_t ncnn_mp_blob_get_top_shape(mp_obj_t layer_obj, mp_obj_t i_obj) {
    ncnn_layer_t layer = (ncnn_layer_t)mp_obj_get_int(layer_obj);
    int i = mp_obj_get_int(i_obj);

    int dims, w, h, c;
    ncnn_blob_get_top_shape(layer, i, &dims, &w, &h, &c);
    mp_obj_t items[] = {
        mp_obj_new_int(dims),
        mp_obj_new_int(w),
        mp_obj_new_int(h),
        mp_obj_new_int(c),
    };
    return mp_obj_new_tuple(4, items);
}
static MP_DEFINE_CONST_FUN_OBJ_2(ncnn_mp_blob_get_top_shape_obj, ncnn_mp_blob_get_top_shape);

// ------------------
/* net api */
// ------------------
// c_api:  ncnn_net_t ncnn_net_create(void);
// Python: ncnn_mp.net_create() -> int (handle)
static mp_obj_t ncnn_mp_net_create(void) {
    ncnn_net_t net = ncnn_net_create();
    return mp_obj_new_int_from_ptr(net);
}
static MP_DEFINE_CONST_FUN_OBJ_0(ncnn_mp_net_create_obj, ncnn_mp_net_create);

// c_api:  void ncnn_net_destroy(ncnn_net_t net);
// Python: ncnn_mp.net_destroy(net_handle) -> None
static mp_obj_t ncnn_mp_net_destroy(mp_obj_t net_obj) {
    ncnn_net_t net = (ncnn_net_t)mp_obj_get_int(net_obj);
    ncnn_net_destroy(net);
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_1(ncnn_mp_net_destroy_obj, ncnn_mp_net_destroy);

// c_api:  ncnn_option_t ncnn_net_get_option(ncnn_net_t net);
// Python: ncnn_mp.net_get_option(net_handle) -> int (handle)
static mp_obj_t ncnn_mp_net_get_option(mp_obj_t net_obj) {
    ncnn_net_t net = (ncnn_net_t)mp_obj_get_int(net_obj);
    ncnn_option_t opt = ncnn_net_get_option(net);
    return mp_obj_new_int_from_ptr(opt);
}
static MP_DEFINE_CONST_FUN_OBJ_1(ncnn_mp_net_get_option_obj, ncnn_mp_net_get_option);

// c_api:  void ncnn_net_set_option(ncnn_net_t net, ncnn_option_t opt);
// Python: ncnn_mp.net_set_option(net_handle, opt_handle) -> None
static mp_obj_t ncnn_mp_net_set_option(mp_obj_t net_obj, mp_obj_t opt_obj) {
    ncnn_net_t net = (ncnn_net_t)mp_obj_get_int(net_obj);
    ncnn_option_t opt = (ncnn_option_t)mp_obj_get_int(opt_obj);
    ncnn_net_set_option(net, opt);
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_2(ncnn_mp_net_set_option_obj, ncnn_mp_net_set_option);

#if NCNN_VULKAN
// c_api:  void ncnn_net_set_vulkan_device(ncnn_net_t net, int device_index);
// Python: ncnn_mp.net_set_vulkan_device(net_handle, device_index) -> None
static mp_obj_t ncnn_mp_net_set_vulkan_device(mp_obj_t net_obj, mp_obj_t device_index_obj) {
    ncnn_net_t net = (ncnn_net_t)mp_obj_get_int(net_obj);
    int device_index = mp_obj_get_int(device_index_obj);
    ncnn_net_set_vulkan_device(net, device_index);
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_2(ncnn_mp_net_set_vulkan_device_obj, ncnn_mp_net_set_vulkan_device);
#endif // NCNN_VULKAN

// TODO: ncnn_net_register_custom_layer_by_type
// TODO: ncnn_net_register_custom_layer_by_typeindex

#if NCNN_STDIO
#if NCNN_STRING
// c_api:  int ncnn_net_load_param(ncnn_net_t net, const char* path);
// Python: ncnn_mp.net_load_param(net_handle, path) -> int
static mp_obj_t ncnn_mp_net_load_param(mp_obj_t net_obj, mp_obj_t path_obj) {
    ncnn_net_t net = (ncnn_net_t)mp_obj_get_int(net_obj);
    const char* path = mp_obj_str_get_str(path_obj);
    int result = ncnn_net_load_param(net, path);
    return mp_obj_new_int(result);
}
static MP_DEFINE_CONST_FUN_OBJ_2(ncnn_mp_net_load_param_obj, ncnn_mp_net_load_param);
#endif // NCNN_STRING

// c_api:  int ncnn_net_load_param_bin(ncnn_net_t net, const char* path);
// Python: ncnn_mp.net_load_param_bin(net_handle, path) -> int
static mp_obj_t ncnn_mp_net_load_param_bin(mp_obj_t net_obj, mp_obj_t path_obj) {
    ncnn_net_t net = (ncnn_net_t)mp_obj_get_int(net_obj);
    const char* path = mp_obj_str_get_str(path_obj);
    int result = ncnn_net_load_param_bin(net, path);
    return mp_obj_new_int(result);
}
static MP_DEFINE_CONST_FUN_OBJ_2(ncnn_mp_net_load_param_bin_obj, ncnn_mp_net_load_param_bin);

// c_api:  int ncnn_net_load_model(ncnn_net_t net, const char* path);
// Python: ncnn_mp.net_load_model(net_handle, path) -> int
static mp_obj_t ncnn_mp_net_load_model(mp_obj_t net_obj, mp_obj_t path_obj) {
    ncnn_net_t net = (ncnn_net_t)mp_obj_get_int(net_obj);
    const char* path = mp_obj_str_get_str(path_obj);
    int result = ncnn_net_load_model(net, path);
    return mp_obj_new_int(result);
}
static MP_DEFINE_CONST_FUN_OBJ_2(ncnn_mp_net_load_model_obj, ncnn_mp_net_load_model);
#endif // NCNN_STDIO

#if NCNN_STDIO
#if NCNN_STRING
// c_api:  int ncnn_net_load_param_memory(ncnn_net_t net, const char* mem);
// Python: ncnn_mp.net_load_param_memory(net_handle, mem_str) -> int
static mp_obj_t ncnn_mp_net_load_param_memory(mp_obj_t net_obj, mp_obj_t mem_obj) {
    ncnn_net_t net = (ncnn_net_t)mp_obj_get_int(net_obj);
    const char* mem = mp_obj_str_get_str(mem_obj);
    int result = ncnn_net_load_param_memory(net, mem);
    return mp_obj_new_int(result);
}
static MP_DEFINE_CONST_FUN_OBJ_2(ncnn_mp_net_load_param_memory_obj, ncnn_mp_net_load_param_memory);
#endif // NCNN_STRING
#endif // NCNN_STDIO

// c_api:  int ncnn_net_load_param_bin_memory(ncnn_net_t net, const unsigned char* mem);
// Python: ncnn_mp.net_load_param_bin_memory(net_handle, mem_bytes) -> int
static mp_obj_t ncnn_mp_net_load_param_bin_memory(mp_obj_t net_obj, mp_obj_t mem_obj) {
    ncnn_net_t net = (ncnn_net_t)mp_obj_get_int(net_obj);
    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(mem_obj, &bufinfo, MP_BUFFER_READ);
    int result = ncnn_net_load_param_bin_memory(net, (const unsigned char*)bufinfo.buf);
    return mp_obj_new_int(result);
}
static MP_DEFINE_CONST_FUN_OBJ_2(ncnn_mp_net_load_param_bin_memory_obj, ncnn_mp_net_load_param_bin_memory);

// c_api:  int ncnn_net_load_model_memory(ncnn_net_t net, const unsigned char* mem);
// Python: ncnn_mp.net_load_model_memory(net_handle, mem_bytes) -> int
static mp_obj_t ncnn_mp_net_load_model_memory(mp_obj_t net_obj, mp_obj_t mem_obj) {
    ncnn_net_t net = (ncnn_net_t)mp_obj_get_int(net_obj);
    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(mem_obj, &bufinfo, MP_BUFFER_READ);
    int result = ncnn_net_load_model_memory(net, (const unsigned char*)bufinfo.buf);
    return mp_obj_new_int(result);
}
static MP_DEFINE_CONST_FUN_OBJ_2(ncnn_mp_net_load_model_memory_obj, ncnn_mp_net_load_model_memory);

#if NCNN_STRING
// c_api:  int ncnn_net_load_param_datareader(ncnn_net_t net, const ncnn_datareader_t dr);
// Python: ncnn_mp.net_load_param_datareader(net_handle, dr_handle) -> int
static mp_obj_t ncnn_mp_net_load_param_datareader(mp_obj_t net_obj, mp_obj_t dr_obj) {
    ncnn_net_t net = (ncnn_net_t)mp_obj_get_int(net_obj);
    ncnn_datareader_t dr = (ncnn_datareader_t)mp_obj_get_int(dr_obj);
    int result = ncnn_net_load_param_datareader(net, dr);
    return mp_obj_new_int(result);
}
static MP_DEFINE_CONST_FUN_OBJ_2(ncnn_mp_net_load_param_datareader_obj, ncnn_mp_net_load_param_datareader);
#endif // NCNN_STRING

// c_api:  int ncnn_net_load_param_bin_datareader(ncnn_net_t net, const ncnn_datareader_t dr);
// Python: ncnn_mp.net_load_param_bin_datareader(net_handle, dr_handle) -> int
static mp_obj_t ncnn_mp_net_load_param_bin_datareader(mp_obj_t net_obj, mp_obj_t dr_obj) {
    ncnn_net_t net = (ncnn_net_t)mp_obj_get_int(net_obj);
    ncnn_datareader_t dr = (ncnn_datareader_t)mp_obj_get_int(dr_obj);
    int result = ncnn_net_load_param_bin_datareader(net, dr);
    return mp_obj_new_int(result);
}
static MP_DEFINE_CONST_FUN_OBJ_2(ncnn_mp_net_load_param_bin_datareader_obj, ncnn_mp_net_load_param_bin_datareader);

// c_api:  int ncnn_net_load_model_datareader(ncnn_net_t net, const ncnn_datareader_t dr);
// Python: ncnn_mp.net_load_model_datareader(net_handle, dr_handle) -> int
static mp_obj_t ncnn_mp_net_load_model_datareader(mp_obj_t net_obj, mp_obj_t dr_obj) {
    ncnn_net_t net = (ncnn_net_t)mp_obj_get_int(net_obj);
    ncnn_datareader_t dr = (ncnn_datareader_t)mp_obj_get_int(dr_obj);
    int result = ncnn_net_load_model_datareader(net, dr);
    return mp_obj_new_int(result);
}
static MP_DEFINE_CONST_FUN_OBJ_2(ncnn_mp_net_load_model_datareader_obj, ncnn_mp_net_load_model_datareader);

// c_api:  void ncnn_net_clear(ncnn_net_t net);
// Python: ncnn_mp.net_clear(net_handle) -> None
static mp_obj_t ncnn_mp_net_clear(mp_obj_t net_obj) {
    ncnn_net_t net = (ncnn_net_t)mp_obj_get_int(net_obj);
    ncnn_net_clear(net);
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_1(ncnn_mp_net_clear_obj, ncnn_mp_net_clear);

// c_api:  int ncnn_net_get_input_count(const ncnn_net_t net);
// Python: ncnn_mp.net_get_input_count(net_handle) -> int
static mp_obj_t ncnn_mp_net_get_input_count(mp_obj_t net_obj) {
    ncnn_net_t net = (ncnn_net_t)mp_obj_get_int(net_obj);
    int count = ncnn_net_get_input_count(net);
    return mp_obj_new_int(count);
}
static MP_DEFINE_CONST_FUN_OBJ_1(ncnn_mp_net_get_input_count_obj, ncnn_mp_net_get_input_count);

// c_api:  int ncnn_net_get_output_count(const ncnn_net_t net);
// Python: ncnn_mp.net_get_output_count(net_handle) -> int
static mp_obj_t ncnn_mp_net_get_output_count(mp_obj_t net_obj) {
    ncnn_net_t net = (ncnn_net_t)mp_obj_get_int(net_obj);
    int count = ncnn_net_get_output_count(net);
    return mp_obj_new_int(count);
}
static MP_DEFINE_CONST_FUN_OBJ_1(ncnn_mp_net_get_output_count_obj, ncnn_mp_net_get_output_count);

#if NCNN_STRING
// c_api:  const char* ncnn_net_get_input_name(const ncnn_net_t net, int i);
// Python: ncnn_mp.net_get_input_name(net_handle, i) -> str
static mp_obj_t ncnn_mp_net_get_input_name(mp_obj_t net_obj, mp_obj_t i_obj) {
    ncnn_net_t net = (ncnn_net_t)mp_obj_get_int(net_obj);
    int i = mp_obj_get_int(i_obj);
    const char* name = ncnn_net_get_input_name(net, i);
    return mp_obj_new_str(name, strlen(name));
}
static MP_DEFINE_CONST_FUN_OBJ_2(ncnn_mp_net_get_input_name_obj, ncnn_mp_net_get_input_name);

// c_api:  const char* ncnn_net_get_output_name(const ncnn_net_t net, int i);
// Python: ncnn_mp.net_get_output_name(net_handle, i) -> str
static mp_obj_t ncnn_mp_net_get_output_name(mp_obj_t net_obj, mp_obj_t i_obj) {
    ncnn_net_t net = (ncnn_net_t)mp_obj_get_int(net_obj);
    int i = mp_obj_get_int(i_obj);
    const char* name = ncnn_net_get_output_name(net, i);
    return mp_obj_new_str(name, strlen(name));
}
static MP_DEFINE_CONST_FUN_OBJ_2(ncnn_mp_net_get_output_name_obj, ncnn_mp_net_get_output_name);
#endif // NCNN_STRING

// c_api:  int ncnn_net_get_input_index(const ncnn_net_t net, int i);
// Python: ncnn_mp.net_get_input_index(net_handle, i) -> int
static mp_obj_t ncnn_mp_net_get_input_index(mp_obj_t net_obj, mp_obj_t i_obj) {
    ncnn_net_t net = (ncnn_net_t)mp_obj_get_int(net_obj);
    int i = mp_obj_get_int(i_obj);
    int index = ncnn_net_get_input_index(net, i);
    return mp_obj_new_int(index);
}
static MP_DEFINE_CONST_FUN_OBJ_2(ncnn_mp_net_get_input_index_obj, ncnn_mp_net_get_input_index);

// c_api:  int ncnn_net_get_output_index(const ncnn_net_t net, int i);
// Python: ncnn_mp.net_get_output_index(net_handle, i) -> int
static mp_obj_t ncnn_mp_net_get_output_index(mp_obj_t net_obj, mp_obj_t i_obj) {
    ncnn_net_t net = (ncnn_net_t)mp_obj_get_int(net_obj);
    int i = mp_obj_get_int(i_obj);
    int index = ncnn_net_get_output_index(net, i);
    return mp_obj_new_int(index);
}
static MP_DEFINE_CONST_FUN_OBJ_2(ncnn_mp_net_get_output_index_obj, ncnn_mp_net_get_output_index);


// ------------------
/* extractor api */
// ------------------
// c_api:  ncnn_extractor_t ncnn_extractor_create(ncnn_net_t net);
// Python: ncnn_mp.extractor_create(net_handle) -> int (handle)
static mp_obj_t ncnn_mp_extractor_create(mp_obj_t net_obj) {
    ncnn_net_t net = (ncnn_net_t)mp_obj_get_int(net_obj);
    ncnn_extractor_t ex = ncnn_extractor_create(net);
    return mp_obj_new_int_from_ptr(ex);
}
static MP_DEFINE_CONST_FUN_OBJ_1(ncnn_mp_extractor_create_obj, ncnn_mp_extractor_create);

// c_api:  void ncnn_extractor_destroy(ncnn_extractor_t ex);
// Python: ncnn_mp.extractor_destroy(ex_handle) -> None
static mp_obj_t ncnn_mp_extractor_destroy(mp_obj_t ex_obj) {
    ncnn_extractor_t ex = (ncnn_extractor_t)mp_obj_get_int(ex_obj);
    ncnn_extractor_destroy(ex);
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_1(ncnn_mp_extractor_destroy_obj, ncnn_mp_extractor_destroy);

// c_api:  void ncnn_extractor_set_option(ncnn_extractor_t ex, const ncnn_option_t opt);
// Python: ncnn_mp.extractor_set_option(ex_handle, opt_handle) -> None
static mp_obj_t ncnn_mp_extractor_set_option(mp_obj_t ex_obj, mp_obj_t opt_obj) {
    ncnn_extractor_t ex = (ncnn_extractor_t)mp_obj_get_int(ex_obj);
    ncnn_option_t opt = (ncnn_option_t)mp_obj_get_int(opt_obj);
    ncnn_extractor_set_option(ex, opt);
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_2(ncnn_mp_extractor_set_option_obj, ncnn_mp_extractor_set_option);

#if NCNN_STRING
// c_api:  int ncnn_extractor_input(ncnn_extractor_t ex, const char* name, const ncnn_mat_t mat);
// Python: ncnn_mp.extractor_input(ex_handle, name, mat_handle) -> int
static mp_obj_t ncnn_mp_extractor_input(mp_obj_t ex_obj, mp_obj_t name_obj, mp_obj_t mat_obj) {
    ncnn_extractor_t ex = (ncnn_extractor_t)mp_obj_get_int(ex_obj);
    const char* name = mp_obj_str_get_str(name_obj);
    ncnn_mat_t mat = (ncnn_mat_t)mp_obj_get_int(mat_obj);
    int result = ncnn_extractor_input(ex, name, mat);
    return mp_obj_new_int(result);
}
static MP_DEFINE_CONST_FUN_OBJ_3(ncnn_mp_extractor_input_obj, ncnn_mp_extractor_input);

// c_api:  int ncnn_extractor_extract(ncnn_extractor_t ex, const char* name, ncnn_mat_t* mat);
// Python: ncnn_mp.extractor_extract(ex_handle, name) -> int (handle)
static mp_obj_t ncnn_mp_extractor_extract(mp_obj_t ex_obj, mp_obj_t name_obj) {
    ncnn_extractor_t ex = (ncnn_extractor_t)mp_obj_get_int(ex_obj);
    const char* name = mp_obj_str_get_str(name_obj);
    ncnn_mat_t mat;
    int result = ncnn_extractor_extract(ex, name, &mat);
    // in C: return 0 if success
    if (result != 0) {
        return mp_const_none;
    }
    return mp_obj_new_int_from_ptr(mat);
}
static MP_DEFINE_CONST_FUN_OBJ_2(ncnn_mp_extractor_extract_obj, ncnn_mp_extractor_extract);
#endif // NCNN_STRING

// c_api:  int ncnn_extractor_input_index(ncnn_extractor_t ex, int index, const ncnn_mat_t mat);
// Python: ncnn_mp.extractor_input_index(ex_handle, index, mat_handle) -> int
static mp_obj_t ncnn_mp_extractor_input_index(mp_obj_t ex_obj, mp_obj_t index_obj, mp_obj_t mat_obj) {
    ncnn_extractor_t ex = (ncnn_extractor_t)mp_obj_get_int(ex_obj);
    int index = mp_obj_get_int(index_obj);
    ncnn_mat_t mat = (ncnn_mat_t)mp_obj_get_int(mat_obj);
    int result = ncnn_extractor_input_index(ex, index, mat);
    return mp_obj_new_int(result);
}
static MP_DEFINE_CONST_FUN_OBJ_3(ncnn_mp_extractor_input_index_obj, ncnn_mp_extractor_input_index);

// c_api:  int ncnn_extractor_extract_index(ncnn_extractor_t ex, int index, ncnn_mat_t* mat);
// Python: ncnn_mp.extractor_extract_index(ex_handle, index) -> int (handle)
static mp_obj_t ncnn_mp_extractor_extract_index(mp_obj_t ex_obj, mp_obj_t index_obj) {
    ncnn_extractor_t ex = (ncnn_extractor_t)mp_obj_get_int(ex_obj);
    int index = mp_obj_get_int(index_obj);
    ncnn_mat_t mat;
    int result = ncnn_extractor_extract_index(ex, index, &mat);
    if (result != 0) {
        return mp_const_none;
    }
    return mp_obj_new_int_from_ptr(mat);
}
static MP_DEFINE_CONST_FUN_OBJ_2(ncnn_mp_extractor_extract_index_obj, ncnn_mp_extractor_extract_index);


// ------------------
/* mat process api */
// ------------------
// c_api:  void ncnn_copy_make_border(const ncnn_mat_t src, ncnn_mat_t dst, int top, int bottom, int left, int right, int type, float v, const ncnn_option_t opt);
// Python: ncnn_mp.copy_make_border(src_handle, dst_handle, top, bottom, left, right, type, v, opt_handle) -> None
static mp_obj_t ncnn_mp_copy_make_border(size_t n_args, const mp_obj_t *args) {
    mp_arg_check_num(n_args, 0, 9, 9, false);
    ncnn_mat_t src = (ncnn_mat_t)mp_obj_get_int(args[0]);
    ncnn_mat_t dst = (ncnn_mat_t)mp_obj_get_int(args[1]);
    int top = mp_obj_get_int(args[2]);
    int bottom = mp_obj_get_int(args[3]);
    int left = mp_obj_get_int(args[4]);
    int right = mp_obj_get_int(args[5]);
    int type = mp_obj_get_int(args[6]);
    float v = mp_obj_get_float(args[7]);
    ncnn_option_t opt = (ncnn_option_t)mp_obj_get_int(args[8]);
    ncnn_copy_make_border(src, dst, top, bottom, left, right, type, v, opt);
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(ncnn_mp_copy_make_border_obj, 9, 9, ncnn_mp_copy_make_border);

// c_api:  void ncnn_copy_make_border_3d(const ncnn_mat_t src, ncnn_mat_t dst, int top, int bottom, int left, int right, int front, int behind, int type, float v, const ncnn_option_t opt);
// Python: ncnn_mp.copy_make_border_3d(src_handle, dst_handle, top, bottom, left, right, front, behind, type, v, opt_handle) -> None
static mp_obj_t ncnn_mp_copy_make_border_3d(size_t n_args, const mp_obj_t *args) {
    mp_arg_check_num(n_args, 0, 11, 11, false);
    ncnn_mat_t src = (ncnn_mat_t)mp_obj_get_int(args[0]);
    ncnn_mat_t dst = (ncnn_mat_t)mp_obj_get_int(args[1]);
    int top = mp_obj_get_int(args[2]);
    int bottom = mp_obj_get_int(args[3]);
    int left = mp_obj_get_int(args[4]);
    int right = mp_obj_get_int(args[5]);
    int front = mp_obj_get_int(args[6]);
    int behind = mp_obj_get_int(args[7]);
    int type = mp_obj_get_int(args[8]);
    float v = mp_obj_get_float(args[9]);
    ncnn_option_t opt = (ncnn_option_t)mp_obj_get_int(args[10]);
    ncnn_copy_make_border_3d(src, dst, top, bottom, left, right, front, behind, type, v, opt);
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(ncnn_mp_copy_make_border_3d_obj, 11, 11, ncnn_mp_copy_make_border_3d);

// c_api:  void ncnn_copy_cut_border(const ncnn_mat_t src, ncnn_mat_t dst, int top, int bottom, int left, int right, const ncnn_option_t opt);
// Python: ncnn_mp.copy_cut_border(src_handle, dst_handle, top, bottom, left, right, opt_handle) -> None
static mp_obj_t ncnn_mp_copy_cut_border(size_t n_args, const mp_obj_t *args) {
    mp_arg_check_num(n_args, 0, 7, 7, false);
    ncnn_mat_t src = (ncnn_mat_t)mp_obj_get_int(args[0]);
    ncnn_mat_t dst = (ncnn_mat_t)mp_obj_get_int(args[1]);
    int top = mp_obj_get_int(args[2]);
    int bottom = mp_obj_get_int(args[3]);
    int left = mp_obj_get_int(args[4]);
    int right = mp_obj_get_int(args[5]);
    ncnn_option_t opt = (ncnn_option_t)mp_obj_get_int(args[6]);
    ncnn_copy_cut_border(src, dst, top, bottom, left, right, opt);
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(ncnn_mp_copy_cut_border_obj, 7, 7, ncnn_mp_copy_cut_border);

// c_api:  void ncnn_copy_cut_border_3d(const ncnn_mat_t src, ncnn_mat_t dst, int top, int bottom, int left, int right, int front, int behind, const ncnn_option_t opt);
// Python: ncnn_mp.copy_cut_border_3d(src_handle, dst_handle, top, bottom, left, right, front, behind, opt_handle) -> None
static mp_obj_t ncnn_mp_copy_cut_border_3d(size_t n_args, const mp_obj_t *args) {
    mp_arg_check_num(n_args, 0, 9, 9, false);
    ncnn_mat_t src = (ncnn_mat_t)mp_obj_get_int(args[0]);
    ncnn_mat_t dst = (ncnn_mat_t)mp_obj_get_int(args[1]);
    int top = mp_obj_get_int(args[2]);
    int bottom = mp_obj_get_int(args[3]);
    int left = mp_obj_get_int(args[4]);
    int right = mp_obj_get_int(args[5]);
    int front = mp_obj_get_int(args[6]);
    int behind = mp_obj_get_int(args[7]);
    ncnn_option_t opt = (ncnn_option_t)mp_obj_get_int(args[8]);
    ncnn_copy_cut_border_3d(src, dst, top, bottom, left, right, front, behind, opt);
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(ncnn_mp_copy_cut_border_3d_obj, 9, 9, ncnn_mp_copy_cut_border_3d);


// ------------------------
/* mat pixel drawing api*/
// ------------------------
#if NCNN_PIXEL_DRAWING
// c_api:  void ncnn_draw_rectangle_c1(unsigned char* pixels, int w, int h, int rx, int ry, int rw, int rh, unsigned int color, int thickness);
// Python: ncnn_mp.draw_rectangle_c1(buffer, w, h, rx, ry, rw, rh, color, thickness) -> None
static mp_obj_t ncnn_mp_draw_rectangle_c1(size_t n_args, const mp_obj_t *args) {
    mp_arg_check_num(n_args, 0, 9, 9, false);
    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(args[0], &bufinfo, MP_BUFFER_WRITE);
    int w = mp_obj_get_int(args[1]);
    int h = mp_obj_get_int(args[2]);
    int rx = mp_obj_get_int(args[3]);
    int ry = mp_obj_get_int(args[4]);
    int rw = mp_obj_get_int(args[5]);
    int rh = mp_obj_get_int(args[6]);
    unsigned int color = (unsigned int)mp_obj_get_int(args[7]);
    int thickness = mp_obj_get_int(args[8]);
    ncnn_draw_rectangle_c1((unsigned char*)bufinfo.buf, w, h, rx, ry, rw, rh, color, thickness);
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(ncnn_mp_draw_rectangle_c1_obj, 9, 9, ncnn_mp_draw_rectangle_c1);

// c_api:  void ncnn_draw_rectangle_c2(unsigned char* pixels, int w, int h, int rx, int ry, int rw, int rh, unsigned int color, int thickness);
// Python: ncnn_mp.draw_rectangle_c2(buffer, w, h, rx, ry, rw, rh, color, thickness) -> None
static mp_obj_t ncnn_mp_draw_rectangle_c2(size_t n_args, const mp_obj_t *args) {
    mp_arg_check_num(n_args, 0, 9, 9, false);
    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(args[0], &bufinfo, MP_BUFFER_WRITE);
    int w = mp_obj_get_int(args[1]);
    int h = mp_obj_get_int(args[2]);
    int rx = mp_obj_get_int(args[3]);
    int ry = mp_obj_get_int(args[4]);
    int rw = mp_obj_get_int(args[5]);
    int rh = mp_obj_get_int(args[6]);
    unsigned int color = (unsigned int)mp_obj_get_int(args[7]);
    int thickness = mp_obj_get_int(args[8]);
    ncnn_draw_rectangle_c2((unsigned char*)bufinfo.buf, w, h, rx, ry, rw, rh, color, thickness);
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(ncnn_mp_draw_rectangle_c2_obj, 9, 9, ncnn_mp_draw_rectangle_c2);

// c_api:  void ncnn_draw_rectangle_c3(unsigned char* pixels, int w, int h, int rx, int ry, int rw, int rh, unsigned int color, int thickness);
// Python: ncnn_mp.draw_rectangle_c3(buffer, w, h, rx, ry, rw, rh, color, thickness) -> None
static mp_obj_t ncnn_mp_draw_rectangle_c3(size_t n_args, const mp_obj_t *args) {
    mp_arg_check_num(n_args, 0, 9, 9, false);
    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(args[0], &bufinfo, MP_BUFFER_WRITE);
    int w = mp_obj_get_int(args[1]);
    int h = mp_obj_get_int(args[2]);
    int rx = mp_obj_get_int(args[3]);
    int ry = mp_obj_get_int(args[4]);
    int rw = mp_obj_get_int(args[5]);
    int rh = mp_obj_get_int(args[6]);
    unsigned int color = (unsigned int)mp_obj_get_int(args[7]);
    int thickness = mp_obj_get_int(args[8]);
    ncnn_draw_rectangle_c3((unsigned char*)bufinfo.buf, w, h, rx, ry, rw, rh, color, thickness);
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(ncnn_mp_draw_rectangle_c3_obj, 9, 9, ncnn_mp_draw_rectangle_c3);

// c_api:  void ncnn_draw_rectangle_c4(unsigned char* pixels, int w, int h, int rx, int ry, int rw, int rh, unsigned int color, int thickness);
// Python: ncnn_mp.draw_rectangle_c4(buffer, w, h, rx, ry, rw, rh, color, thickness) -> None
static mp_obj_t ncnn_mp_draw_rectangle_c4(size_t n_args, const mp_obj_t *args) {
    mp_arg_check_num(n_args, 0, 9, 9, false);
    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(args[0], &bufinfo, MP_BUFFER_WRITE);
    int w = mp_obj_get_int(args[1]);
    int h = mp_obj_get_int(args[2]);
    int rx = mp_obj_get_int(args[3]);
    int ry = mp_obj_get_int(args[4]);
    int rw = mp_obj_get_int(args[5]);
    int rh = mp_obj_get_int(args[6]);
    unsigned int color = (unsigned int)mp_obj_get_int(args[7]);
    int thickness = mp_obj_get_int(args[8]);
    ncnn_draw_rectangle_c4((unsigned char*)bufinfo.buf, w, h, rx, ry, rw, rh, color, thickness);
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(ncnn_mp_draw_rectangle_c4_obj, 9, 9, ncnn_mp_draw_rectangle_c4);

// c_api:  void ncnn_draw_text_c1(unsigned char* pixels, int w, int h, const char* text, int x, int y, int fontpixelsize, unsigned int color);
// Python: ncnn_mp.draw_text_c1(buffer, w, h, text, x, y, fontpixelsize, color) -> None
static mp_obj_t ncnn_mp_draw_text_c1(size_t n_args, const mp_obj_t *args) {
    mp_arg_check_num(n_args, 0, 8, 8, false);
    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(args[0], &bufinfo, MP_BUFFER_WRITE);
    int w = mp_obj_get_int(args[1]);
    int h = mp_obj_get_int(args[2]);
    const char* text = mp_obj_str_get_str(args[3]);
    int x = mp_obj_get_int(args[4]);
    int y = mp_obj_get_int(args[5]);
    int fontpixelsize = mp_obj_get_int(args[6]);
    unsigned int color = (unsigned int)mp_obj_get_int(args[7]);
    ncnn_draw_text_c1((unsigned char*)bufinfo.buf, w, h, text, x, y, fontpixelsize, color);
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(ncnn_mp_draw_text_c1_obj, 8, 8, ncnn_mp_draw_text_c1);

// c_api:  void ncnn_draw_text_c2(unsigned char* pixels, int w, int h, const char* text, int x, int y, int fontpixelsize, unsigned int color);
// Python: ncnn_mp.draw_text_c2(buffer, w, h, text, x, y, fontpixelsize, color) -> None
static mp_obj_t ncnn_mp_draw_text_c2(size_t n_args, const mp_obj_t *args) {
    mp_arg_check_num(n_args, 0, 8, 8, false);
    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(args[0], &bufinfo, MP_BUFFER_WRITE);
    int w = mp_obj_get_int(args[1]);
    int h = mp_obj_get_int(args[2]);
    const char* text = mp_obj_str_get_str(args[3]);
    int x = mp_obj_get_int(args[4]);
    int y = mp_obj_get_int(args[5]);
    int fontpixelsize = mp_obj_get_int(args[6]);
    unsigned int color = (unsigned int)mp_obj_get_int(args[7]);
    ncnn_draw_text_c2((unsigned char*)bufinfo.buf, w, h, text, x, y, fontpixelsize, color);
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(ncnn_mp_draw_text_c2_obj, 8, 8, ncnn_mp_draw_text_c2);

// c_api:  void ncnn_draw_text_c3(unsigned char* pixels, int w, int h, const char* text, int x, int y, int fontpixelsize, unsigned int color);
// Python: ncnn_mp.draw_text_c3(buffer, w, h, text, x, y, fontpixelsize, color) -> None
static mp_obj_t ncnn_mp_draw_text_c3(size_t n_args, const mp_obj_t *args) {
    mp_arg_check_num(n_args, 0, 8, 8, false);
    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(args[0], &bufinfo, MP_BUFFER_WRITE);
    int w = mp_obj_get_int(args[1]);
    int h = mp_obj_get_int(args[2]);
    const char* text = mp_obj_str_get_str(args[3]);
    int x = mp_obj_get_int(args[4]);
    int y = mp_obj_get_int(args[5]);
    int fontpixelsize = mp_obj_get_int(args[6]);
    unsigned int color = (unsigned int)mp_obj_get_int(args[7]);
    ncnn_draw_text_c3((unsigned char*)bufinfo.buf, w, h, text, x, y, fontpixelsize, color);
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(ncnn_mp_draw_text_c3_obj, 8, 8, ncnn_mp_draw_text_c3);

// c_api:  void ncnn_draw_text_c4(unsigned char* pixels, int w, int h, const char* text, int x, int y, int fontpixelsize, unsigned int color);
// Python: ncnn_mp.draw_text_c4(buffer, w, h, text, x, y, fontpixelsize, color) -> None
static mp_obj_t ncnn_mp_draw_text_c4(size_t n_args, const mp_obj_t *args) {
    mp_arg_check_num(n_args, 0, 8, 8, false);
    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(args[0], &bufinfo, MP_BUFFER_WRITE);
    int w = mp_obj_get_int(args[1]);
    int h = mp_obj_get_int(args[2]);
    const char* text = mp_obj_str_get_str(args[3]);
    int x = mp_obj_get_int(args[4]);
    int y = mp_obj_get_int(args[5]);
    int fontpixelsize = mp_obj_get_int(args[6]);
    unsigned int color = (unsigned int)mp_obj_get_int(args[7]);
    ncnn_draw_text_c4((unsigned char*)bufinfo.buf, w, h, text, x, y, fontpixelsize, color);
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(ncnn_mp_draw_text_c4_obj, 8, 8, ncnn_mp_draw_text_c4);

// c_api:  void ncnn_draw_circle_c1(unsigned char* pixels, int w, int h, int cx, int cy, int radius, unsigned int color, int thickness);
// Python: ncnn_mp.draw_circle_c1(buffer, w, h, cx, cy, radius, color, thickness) -> None
static mp_obj_t ncnn_mp_draw_circle_c1(size_t n_args, const mp_obj_t *args) {
    mp_arg_check_num(n_args, 0, 8, 8, false);
    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(args[0], &bufinfo, MP_BUFFER_WRITE);
    int w = mp_obj_get_int(args[1]);
    int h = mp_obj_get_int(args[2]);
    int cx = mp_obj_get_int(args[3]);
    int cy = mp_obj_get_int(args[4]);
    int radius = mp_obj_get_int(args[5]);
    unsigned int color = (unsigned int)mp_obj_get_int(args[6]);
    int thickness = mp_obj_get_int(args[7]);
    ncnn_draw_circle_c1((unsigned char*)bufinfo.buf, w, h, cx, cy, radius, color, thickness);
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(ncnn_mp_draw_circle_c1_obj, 8, 8, ncnn_mp_draw_circle_c1);

// c_api:  void ncnn_draw_circle_c2(unsigned char* pixels, int w, int h, int cx, int cy, int radius, unsigned int color, int thickness);
// Python: ncnn_mp.draw_circle_c2(buffer, w, h, cx, cy, radius, color, thickness) -> None
static mp_obj_t ncnn_mp_draw_circle_c2(size_t n_args, const mp_obj_t *args) {
    mp_arg_check_num(n_args, 0, 8, 8, false);
    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(args[0], &bufinfo, MP_BUFFER_WRITE);
    int w = mp_obj_get_int(args[1]);
    int h = mp_obj_get_int(args[2]);
    int cx = mp_obj_get_int(args[3]);
    int cy = mp_obj_get_int(args[4]);
    int radius = mp_obj_get_int(args[5]);
    unsigned int color = (unsigned int)mp_obj_get_int(args[6]);
    int thickness = mp_obj_get_int(args[7]);
    ncnn_draw_circle_c2((unsigned char*)bufinfo.buf, w, h, cx, cy, radius, color, thickness);
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(ncnn_mp_draw_circle_c2_obj, 8, 8, ncnn_mp_draw_circle_c2);

// c_api:  void ncnn_draw_circle_c3(unsigned char* pixels, int w, int h, int cx, int cy, int radius, unsigned int color, int thickness);
// Python: ncnn_mp.draw_circle_c3(buffer, w, h, cx, cy, radius, color, thickness) -> None
static mp_obj_t ncnn_mp_draw_circle_c3(size_t n_args, const mp_obj_t *args) {
    mp_arg_check_num(n_args, 0, 8, 8, false);
    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(args[0], &bufinfo, MP_BUFFER_WRITE);
    int w = mp_obj_get_int(args[1]);
    int h = mp_obj_get_int(args[2]);
    int cx = mp_obj_get_int(args[3]);
    int cy = mp_obj_get_int(args[4]);
    int radius = mp_obj_get_int(args[5]);
    unsigned int color = (unsigned int)mp_obj_get_int(args[6]);
    int thickness = mp_obj_get_int(args[7]);
    ncnn_draw_circle_c3((unsigned char*)bufinfo.buf, w, h, cx, cy, radius, color, thickness);
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(ncnn_mp_draw_circle_c3_obj, 8, 8, ncnn_mp_draw_circle_c3);

// c_api:  void ncnn_draw_circle_c4(unsigned char* pixels, int w, int h, int cx, int cy, int radius, unsigned int color, int thickness);
// Python: ncnn_mp.draw_circle_c4(buffer, w, h, cx, cy, radius, color, thickness) -> None
static mp_obj_t ncnn_mp_draw_circle_c4(size_t n_args, const mp_obj_t *args) {
    mp_arg_check_num(n_args, 0, 8, 8, false);
    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(args[0], &bufinfo, MP_BUFFER_WRITE);
    int w = mp_obj_get_int(args[1]);
    int h = mp_obj_get_int(args[2]);
    int cx = mp_obj_get_int(args[3]);
    int cy = mp_obj_get_int(args[4]);
    int radius = mp_obj_get_int(args[5]);
    unsigned int color = (unsigned int)mp_obj_get_int(args[6]);
    int thickness = mp_obj_get_int(args[7]);
    ncnn_draw_circle_c4((unsigned char*)bufinfo.buf, w, h, cx, cy, radius, color, thickness);
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(ncnn_mp_draw_circle_c4_obj, 8, 8, ncnn_mp_draw_circle_c4);

// c_api:  void ncnn_draw_line_c1(unsigned char* pixels, int w, int h, int x0, int y0, int x1, int y1, unsigned int color, int thickness);
// Python: ncnn_mp.draw_line_c1(buffer, w, h, x0, y0, x1, y1, color, thickness) -> None
static mp_obj_t ncnn_mp_draw_line_c1(size_t n_args, const mp_obj_t *args) {
    mp_arg_check_num(n_args, 0, 9, 9, false);
    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(args[0], &bufinfo, MP_BUFFER_WRITE);
    int w = mp_obj_get_int(args[1]);
    int h = mp_obj_get_int(args[2]);
    int x0 = mp_obj_get_int(args[3]);
    int y0 = mp_obj_get_int(args[4]);
    int x1 = mp_obj_get_int(args[5]);
    int y1 = mp_obj_get_int(args[6]);
    unsigned int color = (unsigned int)mp_obj_get_int(args[7]);
    int thickness = mp_obj_get_int(args[8]);
    ncnn_draw_line_c1((unsigned char*)bufinfo.buf, w, h, x0, y0, x1, y1, color, thickness);
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(ncnn_mp_draw_line_c1_obj, 9, 9, ncnn_mp_draw_line_c1);

// c_api:  void ncnn_draw_line_c2(unsigned char* pixels, int w, int h, int x0, int y0, int x1, int y1, unsigned int color, int thickness);
// Python: ncnn_mp.draw_line_c2(buffer, w, h, x0, y0, x1, y1, color, thickness) -> None
static mp_obj_t ncnn_mp_draw_line_c2(size_t n_args, const mp_obj_t *args) {
    mp_arg_check_num(n_args, 0, 9, 9, false);
    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(args[0], &bufinfo, MP_BUFFER_WRITE);
    int w = mp_obj_get_int(args[1]);
    int h = mp_obj_get_int(args[2]);
    int x0 = mp_obj_get_int(args[3]);
    int y0 = mp_obj_get_int(args[4]);
    int x1 = mp_obj_get_int(args[5]);
    int y1 = mp_obj_get_int(args[6]);
    unsigned int color = (unsigned int)mp_obj_get_int(args[7]);
    int thickness = mp_obj_get_int(args[8]);
    ncnn_draw_line_c2((unsigned char*)bufinfo.buf, w, h, x0, y0, x1, y1, color, thickness);
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(ncnn_mp_draw_line_c2_obj, 9, 9, ncnn_mp_draw_line_c2);

// c_api:  void ncnn_draw_line_c3(unsigned char* pixels, int w, int h, int x0, int y0, int x1, int y1, unsigned int color, int thickness);
// Python: ncnn_mp.draw_line_c3(buffer, w, h, x0, y0, x1, y1, color, thickness) -> None
static mp_obj_t ncnn_mp_draw_line_c3(size_t n_args, const mp_obj_t *args) {
    mp_arg_check_num(n_args, 0, 9, 9, false);
    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(args[0], &bufinfo, MP_BUFFER_WRITE);
    int w = mp_obj_get_int(args[1]);
    int h = mp_obj_get_int(args[2]);
    int x0 = mp_obj_get_int(args[3]);
    int y0 = mp_obj_get_int(args[4]);
    int x1 = mp_obj_get_int(args[5]);
    int y1 = mp_obj_get_int(args[6]);
    unsigned int color = (unsigned int)mp_obj_get_int(args[7]);
    int thickness = mp_obj_get_int(args[8]);
    ncnn_draw_line_c3((unsigned char*)bufinfo.buf, w, h, x0, y0, x1, y1, color, thickness);
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(ncnn_mp_draw_line_c3_obj, 9, 9, ncnn_mp_draw_line_c3);

// c_api:  void ncnn_draw_line_c4(unsigned char* pixels, int w, int h, int x0, int y0, int x1, int y1, unsigned int color, int thickness);
// Python: ncnn_mp.draw_line_c4(buffer, w, h, x0, y0, x1, y1, color, thickness) -> None
static mp_obj_t ncnn_mp_draw_line_c4(size_t n_args, const mp_obj_t *args) {
    mp_arg_check_num(n_args, 0, 9, 9, false);
    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(args[0], &bufinfo, MP_BUFFER_WRITE);
    int w = mp_obj_get_int(args[1]);
    int h = mp_obj_get_int(args[2]);
    int x0 = mp_obj_get_int(args[3]);
    int y0 = mp_obj_get_int(args[4]);
    int x1 = mp_obj_get_int(args[5]);
    int y1 = mp_obj_get_int(args[6]);
    unsigned int color = (unsigned int)mp_obj_get_int(args[7]);
    int thickness = mp_obj_get_int(args[8]);
    ncnn_draw_line_c4((unsigned char*)bufinfo.buf, w, h, x0, y0, x1, y1, color, thickness);
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(ncnn_mp_draw_line_c4_obj, 9, 9, ncnn_mp_draw_line_c4);
#endif // NCNN_PIXEL_DRAWING

