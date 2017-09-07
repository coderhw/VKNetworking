#import <Foundation/Foundation.h>

#ifndef _YTKNETWORK_
    #define _YTKNETWORK_

#if __has_include(<YTKNetwork/YTKNetwork.h>)

    FOUNDATION_EXPORT double YTKNetworkVersionNumber;
    FOUNDATION_EXPORT const unsigned char YTKNetworkVersionString[];

    #import <YTKNetwork/YTKRequest.h>
    #import <YTKNetwork/YTKBaseRequest.h>
    #import <YTKNetwork/YTKNetworkAgent.h>
    #import <YTKNetwork/YTKNetworkConfig.h>

#else

    #import "YTKRequest.h"
    #import "YTKBaseRequest.h"
    #import "YTKNetworkAgent.h"
    #import "YTKNetworkConfig.h"

#endif /* __has_include */

#endif /* _YTKNETWORK_ */
