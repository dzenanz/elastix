#ifndef __itkParzenWindowNormalizedMutualInformationImageToImageMetric_H__
#define __itkParzenWindowNormalizedMutualInformationImageToImageMetric_H__

#include "itkParzenWindowHistogramImageToImageMetric.h"

namespace itk
{
	
	/**
	 * \class ParzenWindowNormalizedMutualInformationImageToImageMetric
	 * \brief Computes the normalized mutual information between two images to be 
	 * registered using a method based on Mattes et al.
	 *
	 * ParzenWindowNormalizedMutualInformationImageToImageMetric computes the
   * normalized mutual information between a fixed and moving image to be registered.
	 *
	 * The calculations are based on the method of Mattes et al [1,2]
	 * where the probability density distribution are estimated using
	 * Parzen histograms. Once the PDF's have been contructed, the
   * mutual information is obtained by double summing over the
   * discrete PDF values.
   *
   * Construction of the PDFs is implemented in the superclass
   * ParzenWindowHistogramImageToImageMetric.
	 *
	 * Notes: 
	 * 1. This class returns the negative mutual information value.
	 * 2. This class in not thread safe due the private data structures
	 *     used to the store the marginal and joint pdfs.
	 *
	 * References:
	 * [1] "Nonrigid multimodality image registration"
	 *      D. Mattes, D. R. Haynor, H. Vesselle, T. Lewellen and W. Eubank
	 *      Medical Imaging 2001: Image Processing, 2001, pp. 1609-1620.
	 * [2] "PET-CT Image Registration in the Chest Using Free-form Deformations"
	 *      D. Mattes, D. R. Haynor, H. Vesselle, T. Lewellen and W. Eubank
	 *      IEEE Transactions in Medical Imaging. To Appear.
	 * [3] "Optimization of Mutual Information for MultiResolution Image
	 *      Registration"
	 *      P. Thevenaz and M. Unser
	 *      IEEE Transactions in Image Processing, 9(12) December 2000.
   *
	 * \ingroup Metrics
   * \sa ParzenWindowHistogramImageToImageMetric
	 */

	template <class TFixedImage,class TMovingImage >
		class ParzenWindowNormalizedMutualInformationImageToImageMetric :
	public ParzenWindowHistogramImageToImageMetric< TFixedImage, TMovingImage >
	{
	public:
		
		/** Standard class typedefs. */
		typedef ParzenWindowNormalizedMutualInformationImageToImageMetric					    Self;
		typedef ParzenWindowHistogramImageToImageMetric<
      TFixedImage, TMovingImage >			                                  Superclass;
		typedef SmartPointer<Self>																	        Pointer;
		typedef SmartPointer<const Self>														        ConstPointer;
		
		/** Method for creation through the object factory. */
		itkNewMacro( Self );
		
		/** Run-time type information (and related methods). */
		itkTypeMacro(
      ParzenWindowNormalizedMutualInformationImageToImageMetric, 
      ParzenWindowHistogramImageToImageMetric );

    /** Typedefs from the superclass. */
    typedef typename 
      Superclass::CoordinateRepresentationType              CoordinateRepresentationType;
    typedef typename Superclass::MovingImageType            MovingImageType;
    typedef typename Superclass::MovingImagePixelType       MovingImagePixelType;
    typedef typename Superclass::MovingImageConstPointer    MovingImageConstPointer;
    typedef typename Superclass::FixedImageType             FixedImageType;
    typedef typename Superclass::FixedImageConstPointer     FixedImageConstPointer;
    typedef typename Superclass::FixedImageRegionType       FixedImageRegionType;
    typedef typename Superclass::TransformType              TransformType;
    typedef typename Superclass::TransformPointer           TransformPointer;
    typedef typename Superclass::InputPointType             InputPointType;
    typedef typename Superclass::OutputPointType            OutputPointType;
    typedef typename Superclass::TransformParametersType    TransformParametersType;
    typedef typename Superclass::TransformJacobianType      TransformJacobianType;
    typedef typename Superclass::InterpolatorType           InterpolatorType;
    typedef typename Superclass::InterpolatorPointer        InterpolatorPointer;
    typedef typename Superclass::RealType                   RealType;
    typedef typename Superclass::GradientPixelType          GradientPixelType;
    typedef typename Superclass::GradientImageType          GradientImageType;
    typedef typename Superclass::GradientImagePointer       GradientImagePointer;
    typedef typename Superclass::GradientImageFilterType    GradientImageFilterType;
    typedef typename Superclass::GradientImageFilterPointer GradientImageFilterPointer;
    typedef typename Superclass::FixedImageMaskType         FixedImageMaskType;
    typedef typename Superclass::FixedImageMaskPointer      FixedImageMaskPointer;
    typedef typename Superclass::MovingImageMaskType        MovingImageMaskType;
    typedef typename Superclass::MovingImageMaskPointer     MovingImageMaskPointer;
    typedef typename Superclass::MeasureType                MeasureType;
    typedef typename Superclass::DerivativeType             DerivativeType;
    typedef typename Superclass::ParametersType             ParametersType;
    typedef typename Superclass::FixedImagePixelType        FixedImagePixelType;
    typedef typename Superclass::MovingImageRegionType      MovingImageRegionType;
    typedef typename Superclass::ImageSamplerType           ImageSamplerType;
    typedef typename Superclass::ImageSamplerPointer        ImageSamplerPointer;
    typedef typename Superclass::ImageSampleContainerType   ImageSampleContainerType;
    typedef typename 
      Superclass::ImageSampleContainerPointer               ImageSampleContainerPointer;
    typedef typename Superclass::InternalMaskPixelType      InternalMaskPixelType;
    typedef typename
      Superclass::InternalMovingImageMaskType               InternalMovingImageMaskType;
    typedef typename 
      Superclass::MovingImageMaskInterpolatorType           MovingImageMaskInterpolatorType;
    typedef typename Superclass::FixedImageLimiterType      FixedImageLimiterType;
    typedef typename Superclass::MovingImageLimiterType     MovingImageLimiterType;
    typedef typename
      Superclass::FixedImageLimiterOutputType               FixedImageLimiterOutputType;
    typedef typename
      Superclass::MovingImageLimiterOutputType              MovingImageLimiterOutputType;
		
    /** The fixed image dimension. */
		itkStaticConstMacro( FixedImageDimension, unsigned int,
			FixedImageType::ImageDimension );

		/** The moving image dimension. */
		itkStaticConstMacro( MovingImageDimension, unsigned int,
			MovingImageType::ImageDimension );
 					
		/**  Get the value: the negative normalized mutual information */
		MeasureType GetValue( const ParametersType& parameters ) const;

		/**  Get the value and derivatives for single valued optimizers. */
		void GetValueAndDerivative( const ParametersType& parameters, 
			MeasureType& Value, DerivativeType& Derivative ) const;
 		
	protected:
		
		/** The constructor. */
    ParzenWindowNormalizedMutualInformationImageToImageMetric() {};

		/** The destructor. */
		virtual ~ParzenWindowNormalizedMutualInformationImageToImageMetric() {};

		/** Print Self. */
    void PrintSelf( std::ostream& os, Indent indent ) const;

    /** Protected Typedefs ******************/
  
    /** Typedefs inherited from superclass */
    typedef typename Superclass::FixedImageIndexType                FixedImageIndexType;
	  typedef typename Superclass::FixedImageIndexValueType           FixedImageIndexValueType;
	  typedef typename Superclass::MovingImageIndexType               MovingImageIndexType;
	  typedef typename Superclass::FixedImagePointType                FixedImagePointType;
	  typedef typename Superclass::MovingImagePointType               MovingImagePointType;
    typedef typename Superclass::MovingImageContinuousIndexType     MovingImageContinuousIndexType;
  	typedef	typename Superclass::BSplineInterpolatorType            BSplineInterpolatorType;
    typedef typename Superclass::MovingImageDerivativeFunctionType  MovingImageDerivativeFunctionType;
    typedef typename Superclass::MovingImageDerivativeType          MovingImageDerivativeType;
    typedef typename Superclass::BSplineTransformType               BSplineTransformType;
    typedef typename Superclass::BSplineTransformWeightsType        BSplineTransformWeightsType;
	  typedef typename Superclass::BSplineTransformIndexArrayType     BSplineTransformIndexArrayType;
	  typedef typename Superclass::BSplineCombinationTransformType    BSplineCombinationTransformType;
 	  typedef typename Superclass::BSplineParametersOffsetType        BSplineParametersOffsetType;
    typedef typename Superclass::ParameterIndexArrayType            ParameterIndexArrayType;
    typedef typename Superclass::MovingImageMaskDerivativeType      MovingImageMaskDerivativeType;
    typedef typename Superclass::PDFValueType                       PDFValueType;
		typedef typename Superclass::MarginalPDFType                    MarginalPDFType;
    typedef typename Superclass::JointPDFType                       JointPDFType;
		typedef typename Superclass::JointPDFDerivativesType            JointPDFDerivativesType;
		typedef typename Superclass::JointPDFIndexType                  JointPDFIndexType;
    typedef typename Superclass::JointPDFValueType                  JointPDFValueType;
		typedef typename Superclass::JointPDFRegionType                 JointPDFRegionType;
		typedef typename Superclass::JointPDFSizeType                   JointPDFSizeType;
		typedef typename Superclass::JointPDFDerivativesIndexType       JointPDFDerivativesIndexType;
    typedef typename Superclass::JointPDFDerivativesValueType       JointPDFDerivativesValueType;
		typedef typename Superclass::JointPDFDerivativesRegionType      JointPDFDerivativesRegionType;
		typedef typename Superclass::JointPDFDerivativesSizeType        JointPDFDerivativesSizeType;
    typedef typename Superclass::ParzenValueContainerType           ParzenValueContainerType;
    typedef typename Superclass::KernelFunctionType                 KernelFunctionType;

    /** Replace the marginal probabilities by log(probabilities)
     * Changes the input pdf since they are not needed anymore! */
    virtual void ComputeLogMarginalPDF( MarginalPDFType & pdf ) const;

    /** Compute the normalized mutual information and the jointEntropy
     * NMI = (Ef + Em) / Ej
     * Ef = fixed marginal entropy = - sum_k sum_i p(i,k) log pf(k)
     * Em = moving marginal entropy = - sum_k sum_i p(i,k) log pm(i)
     * Ej = joint entropy = - sum_k sum_i p(i,k) log p(i,k)
     */
    virtual MeasureType ComputeNormalizedMutualInformation( MeasureType & jointEntropy ) const;
   
 	private:
		
		/** The private constructor. */
		ParzenWindowNormalizedMutualInformationImageToImageMetric( const Self& );	// purposely not implemented
		/** The private copy constructor. */
		void operator=( const Self& );															// purposely not implemented
  		
	}; // end class ParzenWindowNormalizedMutualInformationImageToImageMetric

} // end namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkParzenWindowNormalizedMutualInformationImageToImageMetric.hxx"
#endif

#endif // end #ifndef __itkParzenWindowNormalizedMutualInformationImageToImageMetric_H__

