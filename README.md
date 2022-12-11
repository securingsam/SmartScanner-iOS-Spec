<picture>
  <source media="(prefers-color-scheme: dark)" srcset="https://securingsam.com/wp-content/uploads/2022/01/logosam_white.svg">
  <source media="(prefers-color-scheme: light)" srcset="https://securingsam.com/wp-content/uploads/2021/12/logosam_colour.svg">
  <img alt="SAM Seamless Network" src="https://securingsam.com/wp-content/uploads/2022/01/logosam_white.svg" width="190px" style="display: block; margin: 2rem 0 1.5rem 0;">
</picture>

# SmartScanner SDK - Developer Documentation
## SDK Version 1.0.0

- [Installation](#installation)
    - [Minimum system sequirements](#minimum-system-requirements)
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

---

## Installation

### Minimum system requirements

The `SmartScannerSDK` library requires iOS 14.0 or later and Swift 5.0 or later.

>**Note** Apple platforms other than iOS are not currently supported.

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

### Manually

If you prefer not to use dependency managers, you can integrate the `SmartScannerSDSK` into your project manually.

Download the [XCFramework](SmartScannerSDK.xcframework) file and copy it to your Xcode project.

---

## API reference

For a more detailed list of all of the available SDK API methods and types, please refer to the [API reference](API_REFERENCE.md).

---

## Usage

## Example

A full example `ViewModel` class file can be found [here](ScannerViewModelExample.swift).

## Setup

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

### Setup and authentication

The `SmartScannerSDK` library requires a SAM vendor authentication token in order to verify your identity.

Setting up occur anywhere, as long as it happens before using any of the `SmartScannerSDK`'s features. Interacting with any other API methods beforehand, will result in `401` errors.

```swift
SmartScanner.getInstance().setup(token: "yoursamvendortoken")
```

## The Scanner API

### The `Scan` instance

The `Scan` instance is used in order to communicate with the `SmartScannerSDK`.

```swift
let scanner: Scan = SmartScanner.getInstance().getScanInstance()
```

### Quick scan

In order to start scanning, call the [`.scan(params:)`](API_REFERENCE.md#scanparams) method from the `Scan` instance.
This method returns a Combine `AnyPublisher` and provides a [`ScanResult`](API_REFERENCE.md#scanresult) object which contains the data that was collected by the scanner.

```swift
let config = ScanConfig()

scanner.scan(params: config)
    .receive(on: RunLoop.main)
    .sink { completion in
        switch completion {
        case .finished:
            print("Finished!")
        case .failure(let error):
            // Scan process failed. Print the error
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
```

### Observing the scanner's progress

The `Scan` instances exposes an observer instance called [`.observeProgress()`](API_REFERENCE.md#observeprogress) that allows you to observe the progress of the scan (progress is values are ranging 0 - 100).
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

### Observing detected devices

As it might be more suitable to get devices the moment they are detected, The `Scan` instance also exposes an [`.observeDevices()`](API_REFERENCE.md#observedevices) method that returns an array of [`Device`](API_REFERENCE.md#device) items.

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

### Stopping the scan process

In order to stop the currently active scan, you can use the [`.killScan()`](API_REFERENCE.md#killscan) method built into the `Scan` instance.

```swift
scanner.killScan()
```

### Custom scanner configurations

The `scan` method call site accepts a [`ScanConfig`](API_REFERENCE.md#scanconfig) object.

The [`ScanConfig`](API_REFERENCE.md#scanconfig) object allows the SDK client to control some of the scanner's configurations. For example, the following code snippet starts a scan that is using only `PING` to detect devices in the network and sets the scan to last only 2 minutes.

All scanner types can be found within the [`SamScannerType`](API_REFERENCE.md#samscannertype) enum.

>**Note** The default configurations are considered to be optimized for best scan results.

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
