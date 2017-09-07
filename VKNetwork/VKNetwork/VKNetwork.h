#import <Foundation/Foundation.h>

#ifndef _VKNETWORK_
    #define _VKNETWORK_

#if __has_include(<VKNetwork/VKNetwork.h>)

    FOUNDATION_EXPORT double VKNetworkVersionNumber;
    FOUNDATION_EXPORT const unsigned char VKNetworkVersionString[];

    #import <VKNetwork/VKRequest.h>
    #import <VKNetwork/VKBaseRequest.h>
    #import <VKNetwork/VKNetworkAgent.h>
    #import <VKNetwork/VKNetworkConfig.h>

#else

    #import "VKRequest.h"
    #import "VKBaseRequest.h"
    #import "VKNetworkAgent.h"
    #import "VKNetworkConfig.h"

#endif /* __has_include */

#endif /* _VKNETWORK_ */
