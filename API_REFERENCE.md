<picture>
  <source media="(prefers-color-scheme: dark)" srcset="https://securingsam.com/wp-content/uploads/2022/01/logosam_white.svg">
  <source media="(prefers-color-scheme: light)" srcset="https://securingsam.com/wp-content/uploads/2021/12/logosam_colour.svg">
  <img alt="SAM Seamless Network" src="https://securingsam.com/wp-content/uploads/2022/01/logosam_white.svg" width="190px" style="display: block; margin: 2rem 0 1.5rem 0;">
</picture>

# SmartScanner SDK - API Reference

- [setup(token:)](#setuptoken)
- [scan(params:)](#scanparams)
- [observeProgress()](#observeprogress)
- [observeDevices()](#observedevices)
- [killScan()](#killscan)
- [ScanConfig(allowedScannerTypes?, scanTimeInSeconds?)](#scanconfigallowedscannertypes-scantimeinseconds)
- [ScanResult()](#scanresult)
- [SamScannerType](#samscannertype)
- [SamSDKError](#samsdkerror)
- [Device](#device)

---

## `setup(token:)`

Setup and authenticate with the `SmartScannerSDK`.

- Params
    - token: `String`
- Returns: `Void`

```swift
SmartScanner.getInstance().setup(token: "yoursamvendortoken")
```

## `scan(params:)`

Starts a scanning process.

- Params
    - params: `ScanConfig`
- Returns: `AnyPublisher<SmartScannerSDK.ScanResult?, SmartScannerSDK.SamSDKError>`

```swift
SmartScanner.getInstance().getScanInstance().scan(params: ScanConfig())
```

## `observeProgress()`

Observes the scanner's progress (0-100%).

- Returns: `AnyPublisher<Int, Never>`

```swift
SmartScanner.getInstance().getScanInstance().observeProgress()
```

## `observeDevices()`

Observes incoming detected devices.

- Returns: ` AnyPublisher<[SmartScannerSDK.Device], SmartScannerSDK.SamSDKError>`

```swift
SmartScanner.getInstance().getScanInstance().observeDevices()
```

## `killScan()`

Stops the current running scan process.

- Returns: `Void`

```swift
SmartScanner.getInstance().getScanInstance().killScan()
```

## `ScanConfig(allowedScannerTypes?, scanTimeInSeconds?)`

Provides custom scanner configuration for the `Scan` instance.

- Params
    - (Optional) allowedScannerTypes: `[SamScannerType]`
        - Default: All scanner types
    - (Optional) scanTimeInSeconds: `Int`
        - Default: `2000`

```swift
 ScanConfig(allowedScannerTypes: [.PING], scanTimeInSeconds: 2000)
```
## `ScanResult()`

This object contains all of the data collected by the scanner after initiating a new scan session.

```swift
class ScanResult: Codable  {
    // Scan start time
    let dateStr: String

    // WiFi SSID if fetched succesfuly
    let wifiName: String?

    // Total devices found
    let total: Int?

    // Total devices identified
    let identified: Int?

    // All detected devices
    let devices: [Device]?

    // The IP of the devices the scan was started from
    let ipv4: String
}
```

## `SamScannerType`

The available scanner types.

```swift
enum SamScannerType {
    case PING
    case BANNER_GRABBING
    case MDNS
    case SSDP
    case MDNS_HOSTNAME
    case DNS_HOSTNAME
    case NET_BIOS
}
```

## `SamSDKError`

The errors received from the scanner are defined in the following enum and can be accessed when an error is received in the scan result.

>**Note** Every error case contains a description tuple that contains the error code, description and title.

```swift
enum SamSDKError: Error {
    case UNKNOWN
    case MISSING_WIFI_CONNECTION
    case LOST_WIFI_CONNECTION
    case MISSING_LOCATION_PERMISSIONS
    case SCAN_IS_ALREADY_RUNNING
    case UNAUTHORIZED
    case SERVER_ERROR

    var description: (code: Int, description: String, title: String)
}
```

## `Device`

Contains information about a detected device.

```swift
struct Device: Codable. Comparable, Identifiable {
    var id: String
    var iotdevice_id: Int?
    var device_mac: String?
    var iot_type: Int?
    var iot_type_uuid: String?
    var device_type_uuid: String?
    var parental_control: Bool?
    var management_app_installed: Bool?
    var device_type: Int?
    var deviceType: SmartScannerSDK.DeviceType
    var last_seen: Double?
    var mac: String!
    var signalStrength: Int
    var networkInterface: SmartScannerSDK.NetworkInterface
    var ip: String
    var ipv6S: [String]?
    var zoneName: String
    var deviceModel: String?
    var deviceSubModel: String?
    var vendor: String?
    var type: String?
    var product: String?
    var os: String?
    var ownersName: String
    var user_id: Int?
    var deviceIsSecuired: Bool
    var conn_type: Int?
    var device_type_id: Int?
    var av_enforce: Int
    var endpoint_installed: Bool?
    var anti_virus: Bool?
    var ep_capabilities: [String]?
    var software: [String : [String]]?
    var displayName: String
    var hostname: String?
    var cloudID: Int
    var selected: Bool
    var isMoved: Bool
    var isJustconnectedNOw: Bool
    var isIoT: Bool
    var isNew: Bool
    var isParentalControlEnabled: Bool
    var is_online: Bool?
    var isOffline: Bool
    var icon_url: String
}
```