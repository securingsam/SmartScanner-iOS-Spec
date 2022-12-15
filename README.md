<picture>
  <source media="(prefers-color-scheme: dark)" srcset="https://securingsam.com/wp-content/uploads/2022/01/logosam_white.svg">
  <source media="(prefers-color-scheme: light)" srcset="https://securingsam.com/wp-content/uploads/2021/12/logosam_colour.svg">
  <img alt="SAM Seamless Network" src="https://securingsam.com/wp-content/uploads/2021/12/logosam_colour.svg" width="190px" style="display: block; margin: 2rem 0 1.5rem 0;">
</picture>

# SmartScanner SDK - Developer Documentation
## SDK Version 1.0.0

- [Installation](#installation)
    - [Minimum system requirements](#minimum-system-requirements)
    - [Swift Package Manager](#swift-package-manager)
    - [Manually](#manually)
- [API reference](#api-reference)
- [Usage](#usage)
    - [Example](#example)
    - [Setup](#setup)
        - [Importing the library](#importing-the-library)
        - [Setup and authentication](#setup-and-authentication)
    - [The Scanner API](#the-scanner-api)
        - [The `Scan` instance](#the-scan-instance)
        - [Quick scan](#quick-scan)
        - [Observing the scanner's progress](#observing-the-scanners-progress)
        - [Observing detected devices](#observing-detected-devices)
        - [Stopping the scan process](#stopping-the-scan-process)
        - [Custom scanner configurations](#custom-scanner-configurations)
        - [Handling 401 unauthorized errors](#handling-401-unauthorized-errors)

---

<a id="installation"></a>
## Installation

<a id="minimum-system-requirements"></a>
### Minimum system requirements

The `SmartScannerSDK` library requires iOS 14.0 or later and Swift 5.0 or later.

>**Note** Apple platforms other than iOS are not currently supported.

<a id="swift-package-manager"></a>
### Swift Package Manager

The [Swift Package Manager](https://swift.org/package-manager/) is a tool for automating the distribution of Swift code and is integrated into the `swift` compiler.

Once you have your Swift package set up, adding the `SmartScannerSDK` as a dependency is as easy as adding it to the `dependencies` value of your `Package.swift`.

```swift
dependencies: [
    .package(
        url: "https://github.com/securingsam/SmartScanner-iOS-Spec",
        .upToNextMajor(from: "1.0.0")
    )
]
```

<a id="manually"></a>
### Manually

If you prefer not to use dependency managers, you can integrate the `SmartScannerSDSK` into your project manually.

Download the [XCFramework](SmartScannerSDK.xcframework) file and copy it to your Xcode project.

---

<a id="api-reference"></a>
## API reference

For a more detailed list of all of the available SDK API methods and types, please refer to the [API reference](API_REFERENCE.md).

---

<a id="usage"></a>
## Usage

<a id="example"></a>
## Example

A full example `ViewModel` class file can be found [here](ScannerViewModelExample.swift).

<a id="setup"></a>
## Setup

<a id="importing-the-library"></a>
### Importing the library

Importing the library in your Swift code is pretty straightforward

```swift
import SmartScannerSDK
```

It is important to know that this variation will work for compiling and running on **physical devices only**.
In case an iPhone Simulator support is required, please use the following import code snippet:

```swift
#if targetEnvironment(simulator)
import SmartScannerSDKSimulator
#else
import SmartScannerSDK
#endif
```

This will ensure to import the simulator variation of the library when the Xcode target device is an iOS simulator.

>**Note** The simulator variation will compile and run, but the scanner will not work on the iPhone simulator in any way.

<a id="setup-and-authentication"></a>
### Setup and authentication

The `SmartScannerSDK` library requires a SAM vendor authentication token in order to verify your identity.

Setting up occurs anywhere, as long as it happens before using any of the `SmartScannerSDK`'s features. Interacting with any other API methods beforehand will result in `401` errors.

```swift
SmartScanner.getInstance().setup(token: "yoursamvendortoken")
```

<a id="the-scanner-api"></a>
## The Scanner API

<a id="the-scan-instance"></a>
### The `Scan` instance

The `Scan` instance is used in order to communicate with the `SmartScannerSDK`.

```swift
let scanner: Scan = SmartScanner.getInstance().getScanInstance()
```

<a id="quick-scan"></a>
### Quick scan

In order to start scanning, call the [`.scan(params:)`](API_REFERENCE.md#scanparams) method from the `Scan` instance.
This method returns a Combined `AnyPublisher` and provides a [`ScanResult`](API_REFERENCE.md#scanresult) object which contains the data that was collected by the scanner.

```swift
let config = ScanConfig()

scanner.scan(params: config)
    .receive(on: RunLoop.main)
    .sink { completion in
        switch completion {
        case .finished:
            print("Completed!")
        case .failure(let error):
            // Scan process failed. Print the error
            print(error.description)
        }
    } receiveValue: { result in
        // On success, print the list of the detected devices.
        guard
            let result,
            let devices = result.devices
        else {
            print("No devices found")
            return
        }

        print("Devices: \(devices)")
    }
    .store(in: &cancellables)
```

<a id="observing-the-scanners-progress"></a>
### Observing the scanner's progress

The `Scan` instances exposes an observer instance called [`.observeProgress()`](API_REFERENCE.md#observeprogress) that allows you to observe the progress of the scan (progress values ranging from 0 - 100).
The [`.observeProgress()`](API_REFERENCE.md#observeprogress) method returns a new Combine `AnyPublisher` with a value of type `Int` that progress values can be read from.

```swift
scanner
    .observeProgress()
    .receive(on: RunLoop.main)
    .sink { value in
        print("Progress: \(value)")
    }
    .store(in: &cancellables)
```

<a id="observing-detected-devices"></a>
### Observing detected devices

As it is better to get devices when they are detected, The `Scan` instance also exposes an [`.observeDevices()`](API_REFERENCE.md#observedevices) method that returns an array of [`Device`](API_REFERENCE.md#device) items.

This allows you to retrieve a list of detected devices as they are detected.

```swift
scanner
    .observeDevices()
    .receive(on: RunLoop.main)
    .sink(receiveCompletion: { error in
        print("The scanner encountered an error: \(error)")
    }, receiveValue: { devices in
        print("Detected devices: \(devices)")
    })
    .store(in: &cancellables)
```

<a id="stopping-the-scan-process"></a>
### Stopping the scan process

In order to stop the currently active scan, you can use the [`.killScan()`](API_REFERENCE.md#killscan) method built into the `Scan` instance.

```swift
scanner.killScan()
```

<a id="custom-scanner-configurations"></a>
### Custom scanner configurations

The `scan` method accepts a [`ScanConfig`](API_REFERENCE.md#scanconfig) object.

The [`ScanConfig`](API_REFERENCE.md#scanconfig) object allows the SDK client to control the scanner's configurations. For example, the following code snippet starts a scan that is using only `PING` to detect devices in the network and sets the scan to last only 2 minutes.

All scanner types can be found within the [`SamScannerType`](API_REFERENCE.md#samscannertype) enum.

>**Note** The default configurations are considered to be optimized for the best scan results.

```swift
let config = ScanConfig(
    allowedScannerTypes: [.PING],
    scanTimeInSeconds: 2000
)

scanner.scan(params: config)
    .receive(on: RunLoop.main)
    .sink { ... }
    .store(in: &cancellables)
```

<a id="handling-401-unauthorized-errors"></a>
### Handling 401 Unauthorized errors

In case the authentication token provided in the initialization and authentication phase is expired during the scan process, the scan process will automatically stop and return a [`SamSDKError`](API_REFERENCE.md#samsdkerror) instance with code of `.UNAUTHORIZED` (401).

In that scenario a new/refreshed token must be provided to the SDK by executing the [`.setup(token:)`](API_REFERENCE.md#setuptoken) function again.

```swift
func startScan() {
    let config = ScanConfig()

    scanner.scan(params: config)
        .receive(on: RunLoop.main)
        .sink { [weak self] completion in
            switch completion {
            case .finished:
                print("Finished!")
            case .failure(let error):
                /// Treat an `.UNAUTHORIZED` type error
                if error == .UNAUTHORIZED {
                    self?.handle401UnauthorizedErrorAndRescan()
                    return
                }
                print(error.description)
            }
        } receiveValue: { result in
            // On success, print the list of deteceted devices
            guard
                let result,
                let devices = result.devices
            else {
                print("No devices found")
                return
            }

            print("Devices: \(devices)")
        }
        .store(in: &cancellables)
}

private func handle401UnauthorizedErrorAndRescan() {
    setupScanner(token: refreshToken())
    startScan()
}

private func refreshToken() -> String {
    // Refresh the token and return a new valid one
}
```
