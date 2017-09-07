//
//  VKHeadModel.h
//  MeiFang
//
//  Created by Zengkaisheng on 2017/3/1.
//  Copyright © 2017年 Vanke.com All rights reserved.
//

#import "VKRequestRootModel.h"


static NSString *const VKUserTokenKey = @"usertoken";

@interface VKHeadModel : VKRequestRootModel



@property (nonatomic, copy) NSString *version;      //版本号
@property (nonatomic, copy) NSString *clientOSType; //平台
@property (nonatomic, copy) NSString *Authorization;


@end
