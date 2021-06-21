#ifndef TOMO_ROTATE_HPP
#define TOMO_ROTATE_HPP

#include <armadillo>

#include "geometry.hpp"
#include "affine_transform.hpp"
#include "interpolation.hpp"


/**
    @addtogroup geometry 
    @{

    @section vol_rot Volume Rotation.

    @note The volume rotation code generates different values then MATLAB in
    tests.  This is because the cubic interpolation code in
    tformarray/resampler is incorrect.  In the interpolation paper cited,
    specific values are assigned to points outside of the cubic volume in order
    to maintain order \f$ O(h^3) \f$ accuracy.  Instead the MATLAB code uses a
    padding or fill value for these entries.  Additionally blending and
    extrapolation is carried out for points outside of the cube boundary.
*/

/**

    Construct a new volume generated by interpolation with given size, and base transformation.

    @param inter Interpolation object to use for values
    @param at Transformation to act on the cube
    @param size the size of the output volume.
    @return A cube of values after interpolation.
*/
arma::cube transform(const interpolater &inter, affine_transform &at, arma::uvec3 size);


/**
    Rotate the volume.

    @param vol the volume to rotate/translate
    @param rm rotational matrix to apply.

    @returns A cube produced by rotation and translation of the passed volume, with values produced by interpolation of the old volume.
*/
arma::cube rotate_vol(const arma::cube &vol, const rot_matrix &rm, const arma::vec3 &dx = arma::zeros<arma::vec>(3));


/**
    Rotate the volume and fill in any missing data with the mean of non-missing data.

    This just calls rotate_vol and replaces nan with mean.

    @param vol the volume to rotate
    @param rm the rotation matrix to apply
    @returns The volume after rotation and padding.
*/
arma::cube rotate_vol_pad_mean(const arma::cube &vol, const rot_matrix &rm, const arma::vec3 &dx =  arma::zeros<arma::vec>(3));


/**
    Rotate the volume and fill in any missing data with zeros.

    This just calls rotate_vol and replaces nan with 0.

    @param vol the volume to rotate
    @param rm the rotation matrix to apply

    @returns The volume after rotation and padding.

*/
arma::cube rotate_vol_pad_zero(const arma::cube &vol, const rot_matrix &rm, const arma::vec3 &dx = arma::zeros<arma::vec>(3));

    
/**
    Rotate the mask

    @param mask the mask to rotate
    @param rm  the rotation matrix to apply to the mask
    @returns The new mask.
*/
arma::cube rotate_mask(const arma::cube &mask, const rot_matrix &rm);

/**
  @} // end addtogroup geometry. 
*/
#endif
