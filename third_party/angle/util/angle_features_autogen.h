// GENERATED FILE - DO NOT EDIT.
// Generated by gen_features.py using data from *_features.json.
//
// Copyright 2022 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// angle_features_autogen.h: List of ANGLE features to help enable/disable them in tests.

#ifndef ANGLE_SRC_TESTS_TEST_UTILS_ANGLE_FEATURES_AUTOGEN_H_
#define ANGLE_SRC_TESTS_TEST_UTILS_ANGLE_FEATURES_AUTOGEN_H_

#include "util_export.h"

namespace angle
{
enum class Feature
{
    AddAndTrueToLoopCondition,
    AddMockTextureNoRenderTarget,
    AdjustSrcDstRegionForBlitFramebuffer,
    AllocateNonZeroMemory,
    AllowAstcFormats,
    AllowBufferReadWrite,
    AllowClearForRobustResourceInit,
    AllowCompressedFormats,
    AllowES3OnFL100,
    AllowETCFormats,
    AllowGenerateMipmapWithCompute,
    AllowGenMultipleMipsPerPass,
    AllowInlineConstVertexData,
    AllowMultisampleStoreAndResolve,
    AllowRuntimeSamplerCompareMode,
    AllowSamplerCompareGradient,
    AllowSamplerCompareLod,
    AllowSeparateDepthStencilBuffers,
    AllowTranslateUniformBlockToStructuredBuffer,
    AlwaysCallUseProgramAfterLink,
    AlwaysUnbindFramebufferTexture2D,
    AlwaysUseManagedStorageModeForBuffers,
    AlwaysUseSharedStorageModeForBuffers,
    AlwaysUseStagedBufferUpdates,
    AsyncCommandQueue,
    Avoid1BitAlphaTextureFormats,
    BindTransformFeedbackBufferBeforeBindBufferRange,
    BottomLeftOriginPresentRegionRectangles,
    BresenhamLineRasterization,
    CacheCompiledShader,
    CallClearTwice,
    ClampArrayAccess,
    ClampFragDepth,
    ClampMscRate,
    ClampPointSize,
    ClearToZeroOrOneBroken,
    ClipSrcRegionForBlitFramebuffer,
    CompressVertexData,
    CopyIOSurfaceToNonIOSurfaceForReadOptimization,
    CopyTextureToBufferForReadOptimization,
    DecodeEncodeSRGBForGenerateMipmap,
    DeferFlushUntilEndRenderPass,
    DepthClamping,
    DepthStencilBlitExtraCopy,
    DisableAnisotropicFiltering,
    DisableB5G6R5Support,
    DisableBlendFuncExtended,
    DisableDrawBuffersIndexed,
    DisableFlippingBlitWithCommand,
    DisableGPUSwitchingSupport,
    DisableMultisampledRenderToTexture,
    DisableNativeParallelCompile,
    DisableProgramBinary,
    DisableProgramCachingForTransformFeedback,
    DisableProgrammableBlending,
    DisableRasterizerOrderViews,
    DisableRasterOrderGroups,
    DisableRWTextureTier2Support,
    DisableSemaphoreFd,
    DisableSyncControlSupport,
    DisableTextureClampToBorder,
    DisableTimestampQueries,
    DisableWorkerContexts,
    DisallowMixedDepthStencilLoadOpNoneAndLoad,
    DoesSRGBClearsOnLinearFramebufferAttachments,
    DontInitializeUninitializedLocals,
    DontRelinkProgramsInParallel,
    DontUseLoopsToInitializeVariables,
    DoWhileGLSLCausesGPUHang,
    EglColorspaceAttributePassthrough,
    EmulateAbsIntFunction,
    EmulateAdvancedBlendEquations,
    EmulateAtan2Float,
    EmulateClipDistanceState,
    EmulateCopyTexImage2D,
    EmulateCopyTexImage2DFromRenderbuffers,
    EmulateDithering,
    EmulatedPrerotation180,
    EmulatedPrerotation270,
    EmulatedPrerotation90,
    EmulateImmutableCompressedTexture3D,
    EmulateIsnanFloat,
    EmulateMaxVertexAttribStride,
    EmulatePackSkipRowsAndPackSkipPixels,
    EmulatePixelLocalStorage,
    EmulatePrimitiveRestartFixedIndex,
    EmulateR32fImageAtomicExchange,
    EmulateRGB10,
    EmulateTinyStencilTextures,
    EmulateTransformFeedback,
    EnableAsyncPipelineCacheCompression,
    EnableCaptureLimits,
    EnableMultisampledRenderToTexture,
    EnablePrecisionQualifiers,
    EnablePreRotateSurfaces,
    EnableProgramBinaryForCapture,
    ExpandIntegerPowExpressions,
    ExplicitlyEnablePerSampleShading,
    ExposeNonConformantExtensionsAndVersions,
    FinishDoesNotCauseQueriesToBeAvailable,
    FlushAfterEndingTransformFeedback,
    FlushBeforeDeleteTextureIfCopiedTo,
    FlushOnFramebufferChange,
    ForceAtomicValueResolution,
    ForceBufferGPUStorage,
    ForceContinuousRefreshOnSharedPresent,
    ForceD16TexFilter,
    ForceD24S8AsUnsupported,
    ForceDepthAttachmentInitOnClear,
    ForceFallbackFormat,
    ForceFragmentShaderPrecisionHighpToMediump,
    ForceGlErrorChecking,
    ForceInitShaderVariables,
    ForceMaxUniformBufferSize16KB,
    ForceNearestFiltering,
    ForceNearestMipFiltering,
    ForceNonCSBaseMipmapGeneration,
    ForceRobustResourceInit,
    ForceStaticVertexStrideState,
    ForceSubmitImmutableTextureUpdates,
    ForceTextureLodOffset1,
    ForceTextureLodOffset2,
    ForceTextureLodOffset3,
    ForceTextureLodOffset4,
    ForceWaitForSubmissionToCompleteForQueryResult,
    GetDimensionsIgnoresBaseLevel,
    HasBaseVertexInstancedDraw,
    HasCheapRenderPass,
    HasDepthAutoResolve,
    HasEffectivePipelineCacheSerialization,
    HasEvents,
    HasExplicitMemBarrier,
    HasNonUniformDispatch,
    HasShaderStencilOutput,
    HasStencilAutoResolve,
    HasTextureSwizzle,
    InitFragmentOutputVariables,
    InitializeCurrentVertexAttributes,
    IntelDisableFastMath,
    IntelExplicitBoolCastWorkaround,
    KeepBufferShadowCopy,
    LimitMax3dArrayTextureSizeTo1024,
    LimitMaxColorTargetBitsForTesting,
    LimitMaxDrawBuffersForTesting,
    LimitMaxMSAASamplesTo4,
    LimitWebglMaxTextureSizeTo4096,
    LogMemoryReportCallbacks,
    LogMemoryReportStats,
    LoseContextOnOutOfMemory,
    MapUnspecifiedColorSpaceToPassThrough,
    MergeProgramPipelineCachesToGlobalCache,
    MrtPerfWorkaround,
    MultisampleColorFormatShaderReadWorkaround,
    MutableMipmapTextureUpload,
    OverrideSurfaceFormatRGB8ToRGBA8,
    PackLastRowSeparatelyForPaddingInclusion,
    PackOverlappingRowsSeparatelyPackBuffer,
    PadBuffersToMaxVertexAttribStride,
    PassHighpToPackUnormSnormBuiltins,
    PerFrameWindowSizeQuery,
    PermanentlySwitchToFramebufferFetchMode,
    PersistentlyMappedBuffers,
    PreAddTexelFetchOffsets,
    PrecisionSafeDivision,
    PreemptivelyStartProvokingVertexCommandBuffer,
    PreferAggregateBarrierCalls,
    PreferCpuForBuffersubdata,
    PreferCPUForBufferSubData,
    PreferDeviceLocalMemoryHostVisible,
    PreferDrawClearOverVkCmdClearAttachments,
    PreferDriverUniformOverSpecConst,
    PreferLinearFilterForYUV,
    PreferMonolithicPipelinesOverLibraries,
    PreferSkippingInvalidateForEmulatedFormats,
    PreferSubmitAtFBOBoundary,
    PreferSubmitOnAnySamplesPassedQueryEnd,
    PromotePackedFormatsTo8BitPerChannel,
    ProvokingVertex,
    QueryCounterBitsGeneratesErrors,
    ReadPixelsUsingImplementationColorReadFormatForNorm16,
    ReapplyUBOBindingsAfterUsingBinaryProgram,
    RegenerateStructNames,
    RemoveDynamicIndexingOfSwizzledVector,
    RemoveInvariantAndCentroidForESSL3,
    ResetTexImage2DBaseLevel,
    RetainSPIRVDebugInfo,
    RewriteFloatUnaryMinusOperator,
    RewriteRepeatedAssignToSwizzled,
    RewriteRowMajorMatrices,
    RewriteUnaryMinusOperator,
    RGBA4IsNotSupportedForColorRendering,
    RGBDXT1TexturesSampleZeroAlpha,
    RoundOutputAfterDithering,
    SanitizeAMDGPURendererString,
    ScalarizeVecAndMatConstructorArgs,
    SelectViewInGeometryShader,
    SetDataFasterThanImageUpload,
    SetPrimitiveRestartFixedIndexForDrawArrays,
    SetZeroLevelBeforeGenerateMipmap,
    ShiftInstancedArrayDataWithOffset,
    SingleThreadedTextureDecompression,
    SkipVSConstantRegisterZero,
    SlowDownMonolithicPipelineCreationForTesting,
    SupportsAndroidHardwareBuffer,
    SupportsAndroidNativeFenceSync,
    SupportsBlendOperationAdvanced,
    SupportsColorWriteEnable,
    SupportsComputeTranscodeEtcToBc,
    SupportsCustomBorderColor,
    SupportsDepthClipControl,
    SupportsDepthStencilResolve,
    SupportsExtendedDynamicState,
    SupportsExtendedDynamicState2,
    SupportsExternalFenceCapabilities,
    SupportsExternalFenceFd,
    SupportsExternalMemoryDmaBufAndModifiers,
    SupportsExternalMemoryFd,
    SupportsExternalMemoryFuchsia,
    SupportsExternalMemoryHost,
    SupportsExternalSemaphoreCapabilities,
    SupportsExternalSemaphoreFd,
    SupportsExternalSemaphoreFuchsia,
    SupportsFilteringPrecision,
    SupportsFragmentShaderInterlockARB,
    SupportsFragmentShaderInterlockNV,
    SupportsFragmentShaderOrderingINTEL,
    SupportsFragmentShaderPixelInterlock,
    SupportsFragmentShadingRate,
    SupportsGeometryStreamsCapability,
    SupportsGGPFrameToken,
    SupportsGraphicsPipelineLibrary,
    SupportsHostQueryReset,
    SupportsImage2dViewOf3d,
    SupportsImageCubeArray,
    SupportsImageFormatList,
    SupportsImagelessFramebuffer,
    SupportsIncrementalPresent,
    SupportsIndexTypeUint8,
    SupportsLockSurfaceExtension,
    SupportsLogicOpDynamicState,
    SupportsMemoryBudget,
    SupportsMixedReadWriteDepthStencilLayouts,
    SupportsMultiDrawIndirect,
    SupportsMultisampledRenderToSingleSampled,
    SupportsMultisampledRenderToSingleSampledGOOGLEX,
    SupportsMultiview,
    SupportsNegativeViewport,
    SupportsPipelineCreationCacheControl,
    SupportsPipelineCreationFeedback,
    SupportsPipelineProtectedAccess,
    SupportsPipelineRobustness,
    SupportsPipelineStatisticsQuery,
    SupportsPresentation,
    SupportsPrimitivesGeneratedQuery,
    SupportsPrimitiveTopologyListRestart,
    SupportsProtectedMemory,
    SupportsRasterizationOrderAttachmentAccess,
    SupportsRenderpass2,
    SupportsRenderPassLoadStoreOpNone,
    SupportsRenderPassStoreOpNone,
    SupportsShaderFloat16,
    SupportsShaderFramebufferFetch,
    SupportsShaderFramebufferFetchEXT,
    SupportsShaderFramebufferFetchNonCoherent,
    SupportsShaderFramebufferFetchNonCoherentEXT,
    SupportsShaderPixelLocalStorageEXT,
    SupportsShaderStencilExport,
    SupportsSharedPresentableImageExtension,
    SupportsSurfaceCapabilities2Extension,
    SupportsSurfacelessQueryExtension,
    SupportsSurfaceProtectedCapabilitiesExtension,
    SupportsSurfaceProtectedSwapchains,
    SupportsTimestampSurfaceAttribute,
    SupportsTransformFeedbackExtension,
    SupportsVertexInputDynamicState,
    SupportsYUVSamplerConversion,
    SupportsYuvTarget,
    SwapbuffersOnFlushOrFinishWithSingleBuffer,
    SyncMonolithicPipelinesToBlobCache,
    SyncVertexArraysToDefault,
    UnbindFBOBeforeSwitchingContext,
    UnfoldShortCircuits,
    UnpackLastRowSeparatelyForPaddingInclusion,
    UnpackOverlappingRowsSeparatelyUnpackBuffer,
    UnsizedSRGBReadPixelsDoesntTransform,
    UploadDataToIosurfacesWithStagingBuffers,
    UploadTextureDataInChunks,
    UseInstancedPointSpriteEmulation,
    UseMultipleDescriptorsForExternalFormats,
    UseNonZeroStencilWriteMaskStaticState,
    UseShadowBuffersWhenAppropriate,
    UseSystemMemoryForConstantBuffers,
    UseUnusedBlocksWithStandardOrSharedLayout,
    VaryingsRequireMatchingPrecisionInSpirv,
    VertexIDDoesNotIncludeBaseVertex,
    WaitIdleBeforeSwapchainRecreation,
    WarmUpPipelineCacheAtLink,
    ZeroMaxLodWorkaround,

    InvalidEnum,
    EnumCount = InvalidEnum,
};

ANGLE_UTIL_EXPORT extern const char *GetFeatureName(Feature feature);

}  // namespace angle

#endif  // ANGLE_SRC_TESTS_TEST_UTILS_ANGLE_FEATURES_AUTOGEN_H_