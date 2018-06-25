//
//  SPSDKPay.h
//  SPSDKPay
//
//  Created by z on 2018/5/24.
//  Copyright © 2018年 super. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>

static NSInteger const kSPSDKPayErrorCode = 400; //渠道支付错误码
static NSInteger const kSPSDKPaySuccessCode = 200; //渠道支付成功码

static NSString * _Nullable const kSPSDKPaySuccessMessage =  @"支付成功";
static NSString * _Nullable const kSPSDKPayFailureMessage = @"支付失败";
static NSString * _Nullable const kSPSDKPayCancelMessage = @"支付取消";

/**
 支付渠道
 */
typedef NS_ENUM(NSInteger , SPSDKPaymentChannel){
    /**
     *  alipay支付渠道
     */
    SPSDKPaymentChannelAliPay,
    /**
     *  银联支付渠道
     */
    SPSDKPaymentChannelUNinPay,
    /**
     *  微信支付渠道
     */
    SPSDKPaymentChannelWX,
};

/**
 *  错误状态码
 */
typedef NS_ENUM(NSUInteger, SPSDKPayErrorOption)
{
    /**
     *  无效的订单对象 (格式错误, Nil)
     */
    SPSDKPayErrorOptionInvalidCharge, 
    /**
     *  无效的证书
     */
    SPSDKPayErrorOptionInvalidCredential,
    /**
     *  无效的渠道
     */
    SPSDKPayErrorOptionInvalidChannel,
    /**
     *  微信没有安装/版本太低
     */
    SPSDKPayErrorOptionWxNotInstalled,
    /**
     *  支付取消
     */
    SPSDKPayErrorOptionCancelled,
    /**
     *  未知取消
     *
     *  银联苹果支付，使用该状态判断
     *  支付取消，交易已发起，状态不确定，商户需查询商户后台确认支付状态
     */
    SPSDKPayErrorOptionUnknownCancel,
    /**
     *  控制器为Nil
     *
     *  银联渠道需要
     */
    SPSDKPayErrorOptionViewControllerIsNil,
    /**
     *  测试发送失败通知
     */
    SPSDKPayErrorOptionTestmodeNotifyFailed,
    /**
     *  渠道返回失败
     */
    SPSDKPayErrorOptionChannelReturnFail,
    /**
     *  连接错误
     */
    SPSDKPayErrorOptionConnectionError,
    /**
     *  未知错误
     */
    SPSDKPayErrorOptionUnknownError,
    /**
     *  请求超时
     */
    SPSDKPayErrorOptionRequestTimeOut,
    /**
     *  处理中
     */
    SPSDKPayErrorOptionProcessing,
};

typedef NS_ENUM(NSUInteger, SPSDKPayRequestContentTypeOption) {
    SPSDKPayRequestContentTypeJSON,
    SPSDKPayRequestContentTypeForm
};

@interface SPSDKPayError : NSObject

@property(readonly, strong) NSError *error;
@property(readonly, assign) SPSDKPayErrorOption code;

- (NSString *)getMsg;

+ (SPSDKPayError *)createError:(NSError *)error code:(SPSDKPayErrorOption)code;

@end

typedef void (^SPSDKPayCompletion)(NSDictionary *result, SPSDKPayError *error);

@interface SPSDKPay : NSObject

/**
 当前渠道服务
 */
@property (nonatomic , strong, readonly) id paymentService;

/**
 *  支付调用接口
 *
 *  @param charge           Charge 对象(JSON 格式字符串 或 NSDictionary)
 *  @param paymentChannel 支付渠道
 *  @param viewController   银联渠道需要
 *  @param scheme           URL Scheme，支付宝渠道回调需要
 *  @param completion 支付结果回调 Block
 */
+ (void)createPayment:(NSObject *)charge
       paymentChannel:(SPSDKPaymentChannel)paymentChannel
       viewController:(UIViewController*)viewController
         appURLScheme:(NSString *)scheme
       withCompletion:(SPSDKPayCompletion)completion;

/**
 *  支付调用接口(支付宝/微信)
 *
 *  @param charge           Charge 对象(JSON 格式字符串 或 NSDictionary)
 *  @param paymentChannel 支付渠道
 *  @param scheme           URL Scheme，支付宝渠道回调需要
 *  @param completion  支付结果回调 Block
 */
+ (void)createPayment:(NSObject *)charge
       paymentChannel:(SPSDKPaymentChannel)paymentChannel
         appURLScheme:(NSString *)scheme
       withCompletion:(SPSDKPayCompletion)completion;

/**
 *  回调结果接口(支付宝/微信/测试模式)
 *
 *  @param url              结果url
 *  @param completion  支付结果回调 Block，保证跳转支付过程中，当 app 被 kill 掉时，能通过这个接口得到支付结果
 *
 *  @return                 当无法处理 URL 或者 URL 格式不正确时，会返回 NO。
 */
+ (BOOL)handleOpenURL:(NSURL *)url
       withCompletion:(SPSDKPayCompletion)completion;

/**
 *  回调结果接口(支付宝/微信/测试模式)
 *
 *  @param url                结果url
 *  @param sourceApplication  源应用 Bundle identifier
 *  @param completion    支付结果回调 Block，保证跳转支付过程中，当 app 被 kill 掉时，能通过这个接口得到支付结果
 *
 *  @return                   当无法处理 URL 或者 URL 格式不正确时，会返回 NO。
 */
+ (BOOL)handleOpenURL:(NSURL *)url
    sourceApplication:(NSString *)sourceApplication
       withCompletion:(SPSDKPayCompletion)completion;

/**
 *  web渠道支付成功后点击 "返回商户" 直接关闭支付页面
 *  @enabled        是否启用
 */
+ (void)ignoreResultUrl:(BOOL)enabled;
/**
 *  版本号
 *
 *  @return         Supay++ SDK 版本号
 */
+ (NSString *)version;

/**
 *  设置 Debug 模式
 *
 *  @param enabled    是否启用
 */
+ (void)setDebugMode:(BOOL)enabled;

/**
 *  设置 App ID
 *  @param  appId  Supay++ 的应用 ID，请登录 https://xxxxxx.com 查看
 */
+ (void)setAppId:(NSString *)appId;


+ (NSString *)appId;

/**
 *  设置请求的 Content-Type
 *  @param  type  可设置为 JSON 或 Form，默认为 JSON
 */
+ (void)setRequestContentType:(SPSDKPayRequestContentTypeOption)type;

+ (SPSDKPayRequestContentTypeOption)requestContentType;


/**
 *  允许 https 自签证书，当你的 chargeURL 为 https 且为自签证书时使用该方法设置
 *  @param  allowInvalidCertificates BOOL
 */
+ (void)setAllowInvalidCertificates:(BOOL)allowInvalidCertificates;

+ (BOOL)allowInvalidCertificates;

/**
 *  设置网络请求延时（使用壹收款或者应用内快捷支付时有用）
 *
 *  @param timeout  延时时间，单位：秒
 */
+ (void)setNetworkTimeout:(NSTimeInterval)timeout;


@end
