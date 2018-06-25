# Supay iOS SDK


## 目录
* [1. 简介](#1)
* [2. 版本要求](#2)
* [3. 接入方法](#3)
    * [3. 使用 CocoaPods](#3.1)
    * [3. 手动导入](#3.2)
* [4. 接入方法](#4)
    * [4.1 使用 Supay++ 标准版 SDK](#4.1)
    * [4.2 使用 Supay++ UI版 SDK](#4.2)
    * [4.3 接收并处理交易结果](#4.3)
* [5. 额外配置](#5)
* [6. 注意事项](#6)

## <h2 id='1'>简介</h2>
lib 文件夹下是 iOS SDK 文件，  
example 文件夹里面是一个简单的接入示例，该示例仅供参考。

__当前版本，不需要微信的 SDK，可以正常调用微信支付__

## <h2 id='2'>版本要求</h2>

iOS SDK 要求 iOS 7.0 及以上版本

## <h2 id='3'>接入方法</h2>
### <h3 id='3.1'>使用 CocoaPods</h3>

1. 在 `Podfile` 添加

    ```
    pod 'SPSDKPay', '~> 1.1.0'
    ```

    默认会包含支付宝、微信。你也可以自己选择渠道。  
    目前支持以下模块：
    - `Alipay`（支付宝移动支付）
    - `CBAlipay`（支付宝移动支付 - 境外支付）
    - `AlipayNoUTDID`（支付宝移动支付，独立 `UTDID.framework`）
    - `Wx`（微信 App 支付）
    - `UI`（Supay++ SDK UI 版）
    - 更新中...

    例如：

    ```
    pod 'SPSDKPay/Alipay', '~> 1.1.0'
    pod 'SPSDKPay/UnionPay', '~> 1.1.0'
   
    ```
    Super++ SDK UI 版
    ```
    pod 'SPSDKPay/UI', '~> 1.1.0'
    ```

2. 运行 `pod install`
3. 从现在开始使用 `.xcworkspace` 打开项目，而不是 `.xcodeproj`
4. 添加 URL Schemes：在 Xcode 中，选择你的工程设置项，选中 "TARGETS" 一栏，在 "Info" 标签栏的 "URL Types" 添加 "URL Schemes"，如果使用微信，填入所注册的微信应用程序 id，如果不使用微信，则自定义，允许英文字母和数字，首字母必须是英文字母，建议起名稍复杂一些，尽量避免与其他程序冲突。
5. 1.0.1 及以上版本，可打开 Debug 模式，打印出 log，方便调试。开启方法：`[SPSDKPay setDebugMode:YES];`。


### <h3 id='3.2'>手动导入</h3>
1. 获取 SDK  
下载 SDK, 里面包含了 lib 文件夹和 example 文件夹。lib 文件夹里面是 SDK 的文件。
2. 依赖 Frameworks：
    必需：
    ```
    CFNetwork.framework
    SystemConfiguration.framework
    Security.framework
    QuartzCore.framework
    CoreTelephony.framework
    libc++.tbd
    libz.tbd
    libsqlite3.0.tbd
    libstdc++.tbd
    CoreMotion.framework
    CoreLocation.framework
    ```
    ```

3. 如果不需要某些渠道，删除 `lib/Channels` 下的相应目录即可。
4. 添加 URL Schemes：在 Xcode 中，选择你的工程设置项，选中 "TARGETS" 一栏，在 "Info" 标签栏的 "URL Types" 添加 "URL Schemes"，如果使用微信，填入所注册的微信应用程序 id，如果不使用微信，则自定义，允许英文字母和数字，首字母必须是英文字母，建议起名稍复杂一些，尽量避免与其他程序冲突。
5. 添加 Other Linker Flags：在 Build Settings 搜索 Other Linker Flags ，添加 `-ObjC`。
6. 1.0.1 及以上版本，可打开 Debug 模式，打印出 log，方便调试。开启方法：`[SPSDKPay setDebugMode:YES];`。

## <h2 id='4'>接入方法</h2>
#### <h3 id='4.1'>使用 Super++ 标准版 SDK</h3>
```
#import <SPSDKPay.h>
```
```
[SPSDKPay createPayment:charge
           viewController:viewController
             appURLScheme:kUrlScheme
           withCompletion:^(NSString *result, PingppError *error) {
               if ([result isEqualToString:@"success"]) {
                   // 支付成功
               } else {
                   // 支付失败或取消
                   NSLog(@"Error: code=%lu msg=%@", error.code, [error getMsg]);
               }
}];
```
### <h3 id='4.2'>使用 Supay++ UI版 SDK</h3>
```
#import <SPSDKPay+UI.h>
```
#### 带渠道选择页面
```
/**
 *  设置需要显示的渠道按钮（有序）
 *  @param  channels  渠道数组，与 API 的 channel 字段对应。 例: @[@"wx",@"alipay", @"upacp", @"bfb_wap"]
 */
[SPSDKPay enableChannels:channels];
 
//调起支付页面
[SPSDKPay payWithOrderNo:orderNo // 订单号
                    amount:100 // 金额
                    params:nil // 自定义参数，请求 chargeURL 时，会放在 custom_params 字段
                 chargeURL:chargeURL // 壹收款会向该地址发送请求，该地址需要返回 charge 的 JSON 字符串
              appURLScheme:appURLScheme // Info.plist 中填写的 URL Scheme，支付宝渠道和测试模式需要
            viewController:self // 当前的 ViewController
         completionHandler:^(NSString * _Nonnull result, PingppURLResponse * _Nullable response, NSError * _Nullable error) {
 
        // 根据result判断支付是否成功
        NSLog(@"result=%@", result);
        if (response && response.responseString) {
            NSLog(@"response.responseString=%@", response.responseString);
        }
        if (error) {
            NSLog(@"completion error code:%lu domain:%@ userInfo:%@", error.code, error.domain, error.userInfo);
        }
}];
```
#### 不带渠道选择页面
```
[SPSDKPay createPay:string
       viewController:self
         appURLScheme:kUrlScheme
       withCompletion:^(NSString *result, PingppError *error) {
        // 根据result判断支付是否成功
        NSLog(@"result=%@", result);
        if (response && response.responseString) {
            NSLog(@"response.responseString=%@", response.responseString);
        }
        if (error) {
            NSLog(@"completion error code:%lu domain:%@ userInfo:%@", error.code, error.domain, error.userInfo);
        }
} ];
```
### <h3 id='4.3'>接收并处理交易结果</h3>
##### 请实现 UIApplicationDelegate 的 - application:openURL:xxxx: 方法:
##### iOS 8 及以下
```
- (BOOL)application:(UIApplication *)application
            openURL:(NSURL *)url
  sourceApplication:(NSString *)sourceApplication
         annotation:(id)annotation {

    BOOL canHandleURL = [SPSDKPay handleOpenURL:url withCompletion:nil];

    return canHandleURL;
}
```
##### iOS 9 及以上
```
- (BOOL)application:(UIApplication *)app
            openURL:(NSURL *)url
            options:(NSDictionary *)options {

    BOOL canHandleURL = [SPSDKPay handleOpenURL:url withCompletion:nil];

    return canHandleURL;
}
```
## <h2 id='5'>额外配置</h2>
1. iOS 9 以上版本如果需要使用支付宝和微信渠道，需要在 `Info.plist` 添加以下代码：

    ```
    <key>LSApplicationQueriesSchemes</key>
    <array>
        <string>weixin</string>
        <string>wechat</string>
        <string>alipay</string>
        <string>alipays</string>
        <string>mqq</string>
        <string>uppaysdk</string>
        <string>uppaywallet</string>
        <string>uppayx1</string>
        <string>uppayx2</string>
        <string>uppayx3</string>
    </array>
    ```
2. iOS 9 限制了 http 协议的访问，如果 App 需要访问 `http://`，需要在 `Info.plist` 添加如下代码：

    ```
    <key>NSAppTransportSecurity</key>
    <dict>
        <key>NSAllowsArbitraryLoads</key>
        <true/>
    </dict>
    ```
3. 如果编译失败，遇到错误信息为：

    ```
    XXXXXXX does not contain bitcode. You must rebuild it with bitcode enabled (Xcode setting ENABLE_BITCODE), obtain an updated library from the vendor, or disable bitcode for this target.
    ```
    请到 Xcode 项目的 `Build Settings` 标签页搜索 bitcode，将 `Enable Bitcode` 设置为 `NO`。  

## <h2 id='6'>注意事项</h2>

### * 请勿直接使用客户端支付结果作为最终判定订单状态的依据，支付状态以服务端为准!!!在收到客户端同步返回结果时，请向自己的服务端请求来查询订单状态。

### * 支付宝渠道发生包冲突的情况
使用阿里百川等阿里系的 SDK 时，可能会出现冲突，请尝试使用 `pod 'SPSDKPay/AlipayNoUTDID'` 代替 `pod 'SPSDKPay/Alipay'`。

因为 `CocoaPods` 的限制，只有编译通过的才能上传成功，所以使用时，需要删除项目中已经存在的 `UTDID.framework`。


**关于如何使用 SDK 请参考 [开发者中心](https://www.xxxxxx.com/docs/index) 或者 [example](https://git.rechengit.com/front-end/cheng-pay-ios-sdk) 文件夹里的示例。**
