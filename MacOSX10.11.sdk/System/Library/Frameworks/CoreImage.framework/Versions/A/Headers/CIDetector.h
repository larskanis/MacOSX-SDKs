/* CoreImage - CIDetector.h

   Copyright (c) 2011 Apple, Inc.
   All rights reserved. */


#import <CoreImage/CoreImageDefines.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

#if __has_feature(objc_generics)
# define CI_DICTIONARY(KeyType, ValueType) NSDictionary<KeyType, ValueType>
# define CI_ARRAY(ValueType) NSArray <ValueType>
#else
# define CI_DICTIONARY(KeyType, ValueType) NSDictionary
# define CI_ARRAY(ValueType) NSArray
#endif


@class CIImage;
@class CIContext;
@class CIFeature;


/** Detects features in images.
 
 This class potentially holds onto a lot of state. Hence it may be beneficial from a performance perspective to re-use the same CIDetector instance. Specifying a CIContext when creating a detector may have an impact on performance since this context may be used when analyzing an image.
 */
NS_CLASS_AVAILABLE(10_7, 5_0)
@interface CIDetector : NSObject {}

/** Returns a new detector instance of the given type.
 
 The type is used to specify the usage intent.
 
 The context argument specifies the CIContext to be used to operate on the image. May be nil.
 
 If the input image to -featuresInImage: is the output of a CoreImage operation, it may improve performance to specify the same context that was used to operate on that image.
 
 The detector may do image processing in this context and if the image is on the GPU and the specified context is a GPU context this may avoid additional upload to / download from the GPU. If the input image is on the CPU (or the output from a CPU based context) specifying a GPU based context (or vice versa) may reduce performance.
 
 The options parameter lets you optinally specify a accuracy / performance tradeoff. Can be nil or an empty dictionary. */
+ (CIDetector *)detectorOfType:(NSString*)type
                       context:(nullable CIContext *)context
                       options:(nullable CI_DICTIONARY(NSString*,id) *)options
    NS_AVAILABLE(10_7, 5_0);

/** Returns an array of CIFeature instances in the given image.
 The array is sorted by confidence, highest confidence first. */
- (CI_ARRAY(CIFeature*) *)featuresInImage:(CIImage *)image
    NS_AVAILABLE(10_7, 5_0);

/** Returns an array of CIFeature instances in the given image.
 The array is sorted by confidence, highest confidence first. 
 The options dictionary can contain a CIDetectorImageOrientation key value. */
- (CI_ARRAY(CIFeature*) *)featuresInImage:(CIImage *)image
                                  options:(nullable CI_DICTIONARY(NSString*,id) *)options
    NS_AVAILABLE(10_8, 5_0);

@end


// Types to be used for +[CIDetector detectorOfType:context:options:]

/* Specifies a detector type for face recognition. */
CORE_IMAGE_EXPORT NSString* const CIDetectorTypeFace NS_AVAILABLE(10_7, 5_0);

/* Specifies a detector type for rectangle detection. */
CORE_IMAGE_EXPORT NSString* const CIDetectorTypeRectangle NS_AVAILABLE(10_10, 8_0);

/* Specifies a detector type for barcode detection. */
CORE_IMAGE_EXPORT NSString* const CIDetectorTypeQRCode NS_AVAILABLE(10_10, 8_0);

/* Specifies a detector type for text detection. */
#if __OBJC2__
CORE_IMAGE_EXPORT NSString* const CIDetectorTypeText NS_AVAILABLE(10_11, 9_0);
#endif

// Options that can be used with +[CIDetector detectorOfType:context:options:]

/* The key in the options dictionary used to specify a accuracy / performance tradeoff to be used. */
CORE_IMAGE_EXPORT NSString* const CIDetectorAccuracy NS_AVAILABLE(10_7, 5_0);

/* These are values to be used with the CIDetectorAccuracy key when created a CIDetector.
 There is a performance / accuracy tradeoff to be made. The default value will work well for most
 situations, but using these the detector will favour performance over accuracy or
 accuracy over performance. */
CORE_IMAGE_EXPORT NSString* const CIDetectorAccuracyLow NS_AVAILABLE(10_7, 5_0); /* Lower accuracy, higher performance */
CORE_IMAGE_EXPORT NSString* const CIDetectorAccuracyHigh NS_AVAILABLE(10_7, 5_0); /* Lower performance, higher accuracy */

/*The key in the options dictionary used to specify that feature tracking should be used. */
CORE_IMAGE_EXPORT NSString* const CIDetectorTracking NS_AVAILABLE(10_8, 6_0);

/* The key in the options dictionary used to specify the minimum size that the 
 detector will recognize as a feature.  The value for this key is an float NSNumber 
 from 0.0 ... 1.0 that represents a fraction of the minor dimension of the image. */

/* For rectangle detector, the value for this key is from 0.2 ... 1.0*/
CORE_IMAGE_EXPORT NSString* const CIDetectorMinFeatureSize NS_AVAILABLE(10_8, 6_0);

/* The key in the options dictionary used to specify number of angles, the value for this key is one of 1, 3, 5, 7, 9, 11.*/
CORE_IMAGE_EXPORT NSString* const CIDetectorNumberOfAngles NS_AVAILABLE(10_11, 9_0);

// Options that can be used with -[CIDetector featuresInImage:options:]

/* The value for this key is an integer NSNumber from 1..8 such as that
 found in kCGImagePropertyOrientation.  If present, the detection will be done
 based on that orientation but the coordinates in the returned features will
 still be based on those of the image. */
CORE_IMAGE_EXPORT NSString *const CIDetectorImageOrientation NS_AVAILABLE(10_8, 5_0);

/* The value for this key is a bool NSNumber. If true, facial expressions, such as blinking and closed eyes are extracted */
CORE_IMAGE_EXPORT NSString *const CIDetectorEyeBlink NS_AVAILABLE(10_9, 7_0);


/* The value for this key is a bool NSNumber. If true, facial expressions, such as smile are extracted */
CORE_IMAGE_EXPORT NSString *const CIDetectorSmile NS_AVAILABLE(10_9, 7_0);

/* The value for this key is a float NSNumber. Specifies the per frame focal length.  */
CORE_IMAGE_EXPORT NSString* const CIDetectorFocalLength NS_AVAILABLE(10_10, 8_0);

/* The value for this key is a float NSNumber. Specifies the aspect ratio of the rectangle detected.  */
CORE_IMAGE_EXPORT NSString* const CIDetectorAspectRatio NS_AVAILABLE(10_10, 8_0);

#undef CI_DICTIONARY
#undef CI_ARRAY

NS_ASSUME_NONNULL_END