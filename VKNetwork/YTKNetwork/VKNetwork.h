#import <Foundation/Foundation.h>

#ifndef _VKNETWORK_
    #define _VKNETWORK_

#if __has_include(<VKNetwork/VKNetwork.h>)

    FOUNDATION_EXPORT double VKNetworkVersionNumber;
    FOUNDATION_EXPORT const unsigned char VKNetworkVersionString[];

    #import <VKNetwork/YTKRequest.h>
    #import <VKNetwork/YTKBaseRequest.h>
    #import <VKNetwork/YTKNetworkAgent.h>
    #import <VKNetwork/YTKNetworkConfig.h>

#else

    #import "VKRequest.h"
    #import "VKBaseRequest.h"
    #import "VKNetworkAgent.h"
    #import "VKNetworkConfig.h"

#endif /* __has_include */

#endif /* _VKNETWORK_ */
