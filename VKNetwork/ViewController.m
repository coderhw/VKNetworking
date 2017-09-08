//
//  ViewController.m
//  VKNetwork
//
//  Created by vanke on 2017/8/31.
//  Copyright © 2017年 Evan. All rights reserved.
//

#import "ViewController.h"
#import "VKDBBookQueryRequest.h"


@interface ViewController ()

/**
 * 请求结果显示
 */
@property (weak, nonatomic) IBOutlet UILabel *resultLabel;

@end

@implementation ViewController

- (void)viewDidLoad {
    
    [super viewDidLoad];

}

- (IBAction)getApiRequestGet:(id)sender {
    
    VKDBBookQueryRequest *dbQueryRequest = [[VKDBBookQueryRequest alloc] init];
    [dbQueryRequest startWithCompletionBlockWithSuccess:^(__kindof VKBaseRequest * _Nonnull request) {
        
        NSLog(@"request:%@", request.responseJSONObject);
        self.resultLabel.text = request.responseString;
    } failure:^(__kindof VKBaseRequest * _Nonnull request) {
        
    }];
}

- (IBAction)clearButtonPressed:(id)sender {
    self.resultLabel.text = @"请求结果";
}



@end
