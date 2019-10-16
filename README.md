# Supay iOS SDK


## 目录
* [1. 简介](#1)
* [2. 版本要求](#2)
* [3. 接入方法](#3)
    * [3. 使用 CocoaPods](#3.1)
    * [3. 手动导入](#3.2)
* [4. 接入方法](#4)
    * [4.1 使用 Superpay 标准版 SDK](#4.1)
    * [4.2 接收并处理交易结果](#4.3)
* [5. 额外配置](#5)

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
    pod 'SPSDKPay', '~> 1.1.3'
    ```

    默认会包含支付宝、微信。你也可以自己选择渠道。  
    目前支持以下模块：
    - `Alipay`（支付宝移动支付）
    - `Wx`（微信 App 支付）
    - 更新中...

    例如：

    ```
    pod 'SPSDKPay/Alipay', '~> 1.1.3'
    pod 'SPSDKPay/Wx', '~> 1.1.3'
   
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
#### <h3 id='4.1'>使用 Superpay 标准版 SDK</h3>
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
### <h3 id='4.2'>接收并处理交易结果</h3>
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
