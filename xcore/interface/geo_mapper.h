/*
 * geo_mapper.h - geometry mapper interface
 *
 *  Copyright (c) 2017 Intel Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Author: Wind Yuan <feng.yuan@intel.com>
 */

#ifndef XCAM_INTERFACE_GEO_MAPPER_H
#define XCAM_INTERFACE_GEO_MAPPER_H

#include <xcam_std.h>
#include <video_buffer.h>
#include <interface/data_types.h>

namespace XCam {

class VKDevice;

class GeoMapper
{
public:
    GeoMapper ();
    virtual ~GeoMapper ();
    static SmartPtr<GeoMapper> create_ocl_geo_mapper ();
    static SmartPtr<GeoMapper> create_soft_geo_mapper ();
    static SmartPtr<GeoMapper> create_gl_geo_mapper ();
    static SmartPtr<GeoMapper> create_vk_geo_mapper (const SmartPtr<VKDevice> &dev, const char* name);

    //2D table
    virtual bool set_lookup_table (const PointFloat2 *data, uint32_t width, uint32_t height) = 0;
    bool set_factors (float x, float y);
    void get_factors (float &x, float &y) const;
    bool set_output_size (uint32_t width, uint32_t height);
    void get_output_size (uint32_t &width, uint32_t &height) const;
    bool set_std_output_size (uint32_t width, uint32_t height);
    void get_std_output_size (uint32_t &width, uint32_t &height) const;
    bool set_thread_count (uint32_t x, uint32_t y);
    void get_thread_count (uint32_t &x, uint32_t &y) const;

    virtual XCamReturn remap (
        const SmartPtr<VideoBuffer> &in, SmartPtr<VideoBuffer> &out) = 0;

protected:
    virtual bool auto_calculate_factors (uint32_t lut_w, uint32_t lut_h);

private:
    uint32_t     _out_width, _out_height;
    uint32_t     _std_out_width, _std_out_height;
    uint32_t     _lut_width, _lut_height;
    float        _factor_x, _factor_y;
    uint32_t     _thread_x, _thread_y;
};

}
#endif //XCAM_INTERFACE_GEO_MAPPER_H
