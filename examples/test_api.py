# This file is a Python translation of ncnn/tests/test_c_api.cpp
# It is used to test the object-oriented ncnn_mp MicroPython bindings.

import ncnn_mp
import struct

print(f'Testing MicroPython bindings for ncnn c apis.\nCurrent ncnn version is {ncnn_mp.version()}.\n')

def test_binary_op():
    """
    Tests binary operations using a BinaryOp layer.
    """
    success = False
    try:
        a = ncnn_mp.Mat(w=2)
        b = ncnn_mp.Mat(w=2)
        opt = ncnn_mp.Option()

        # Set values for a and b
        a.fill(2.0)
        b.fill(3.0)

        # Create a BinaryOp layer
        op = ncnn_mp.Layer(type="BinaryOp")

        # Load layer param
        pd = ncnn_mp.ParamDict()
        pd.set_int(0, 0)  # op_type = ADD
        op.load_param(pd)

        # Load an empty model
        mb = ncnn_mp.ModelBin()
        op.load_model(mb)

        op.create_pipeline(opt)

        top_blobs = op.forward([a, b], 1, opt)
        c = top_blobs[0]

        op.destroy_pipeline(opt)

        # Check c == a + b
        if c:
            dims = c.dims
            w = c.w
            c_data_bytes = c.to_bytes()
            c_data_floats = struct.unpack(f'{w}f', c_data_bytes)
            
            print(f"test_binary_op:\nResult dims={dims}, w={w}, data={c_data_floats}\n")
            
            if (dims == 1 and w == 2 and c_data_floats[0] == 5.0 and c_data_floats[1] == 5.0):
                success = True
    
    except Exception as e:
        print(f"An error occurred in test_binary_op: {e}")
        success = False

    return success

def test_reorg_layer():
    """
    Tests the Reorg layer.
    """
    success = False
    try:
        # Create Mat a
        data = [
            0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0,
            10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0,
            20.0, 21.0, 22.0, 23.0, 24.0, 25.0, 26.0, 27.0
        ]
        data_bytes = struct.pack(f'{len(data)}f', *data)
        a = ncnn_mp.Mat(w=24, data=data_bytes, elemsize=4)

        # Create Mat b by reshape
        b = a.reshape(4, 2, 3)

        opt = ncnn_mp.Option()

        # Create a Reorg layer
        op = ncnn_mp.Layer(type="Reorg")
        pd = ncnn_mp.ParamDict()
        pd.set_int(0, 2)  # stride = 2
        op.load_param(pd)
        mb = ncnn_mp.ModelBin()
        op.load_model(mb)

        op.create_pipeline(opt)

        c = op.forward(b, opt)

        op.destroy_pipeline(opt)

        if c:
            # This time we use object attributes directly
            print(f"test_reorg_layer:\nResult dims={c.dims}, w={c.w}, h={c.h}, c={c.c}\n")
            
            if not (c.dims == 3 and c.w == 2 and c.h == 1 and c.c == 12):
                return False

            expected = [
                0.0, 2.0, 1.0, 3.0, 4.0, 6.0, 5.0, 7.0,
                10.0, 12.0, 11.0, 13.0, 14.0, 16.0, 15.0, 17.0,
                20.0, 22.0, 21.0, 23.0, 24.0, 26.0, 25.0, 27.0
            ]
            expected_bytes = struct.pack(f'{len(expected)}f', *expected)
            
            c2 = c.flatten(opt)
            
            if c2.to_bytes() == expected_bytes:
                success = True

    except Exception as e:
        print(f"An error occurred in test_reorg_layer: {e}")
        success = False

    return success

def test_net_extractor():
    """
    Tests end-to-end model loading and inference with Net and Extractor.
    """
    success = False
    try:
        # Define a model in memory
        param_str = "7767517\n2 2\nInput input 0 1 data\nAbsVal abs1 1 1 data output\0"
        
        net = ncnn_mp.Net()
        
        # Load network from memory
        param_dr = ncnn_mp.DataReader(from_memory=param_str)
        net.load_param(param_dr)
        # No model file is needed for this network

        # Input
        in_mat = ncnn_mp.Mat(w=4)
        in_mat.fill(-2.5)

        input_data_bytes = in_mat.to_bytes()
        input_data_floats = struct.unpack(f'{in_mat.w}f', input_data_bytes)
        print(f"test_net_extractor:\nInput data: {input_data_floats}")

        # Run
        ex = net.create_extractor()
        ex.input("data", in_mat)
        out_mat = ex.extract("output")

        # Output
        result_bytes = out_mat.to_bytes()
        result_floats = struct.unpack(f'{out_mat.w}f', result_bytes)

        print(f"Output data after AbsVal layer: {result_floats}\n")

        expected_value = 2.5
        if abs(result_floats[0] - expected_value) < 1e-6:
            success = True

    except Exception as e:
        print(f"An error occurred in test_net_extractor: {e}")
        success = False
    
    return success

if __name__ == "__main__":
    result1 = test_binary_op()
    result2 = test_reorg_layer()
    result3 = test_net_extractor()
    
    print("--- TEST SUMMARY ---")
    print(f"test_binary_op:     {'PASSED' if result1 else 'FAILED'}")
    print(f"test_reorg_layer:   {'PASSED' if result2 else 'FAILED'}")
    print(f"test_net_extractor: {'PASSED' if result3 else 'FAILED'}")

    if result1 and result2 and result3:
        print("\nAll tests passed!")
    else:
        print("\nSome tests failed.")
