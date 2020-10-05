#pragma once

#include <cstdint>
#include <vector>

#include <tensorflow/lite/interpreter.h>
#include <tensorflow/lite/model.h>

class Model 
{
public:
    typedef struct Output {
        float x;
        float y;
        float confidence;
    } Output;
public:
    Model(const char *filepath);
    Output resize_and_predict(uint8_t *image, int image_width, int image_height, int image_channels);
    Output predict();
    void show_info();
public:
    inline float* get_input_buffer(void) { return mInputBuffer; }
    inline int get_input_size() { return mInputSize; }
private:
    int mInputWidth, mInputHeight, mInputChannels, mInputSize;
    std::vector<uint8_t> mResizeBuffer;
    std::unique_ptr<tflite::FlatBufferModel> mModel;
    std::unique_ptr<tflite::Interpreter> mInterpreter;
    float *mInputBuffer;
    float *mOutputBuffer;
};