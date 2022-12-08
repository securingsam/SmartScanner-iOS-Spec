// swift-tools-version:5.6
import PackageDescription

let package = Package(
    name: "SmartScannerSDK",
    platforms: [.iOS(.v14)],
    products: [
        .library(
            name: "SmartScannerSDK",
            targets: ["SmartScannerSDK"]
        )
    ],
    targets: [
        .target(
            name: "SmartScannerSDK"
        ),
        .binaryTarget(
            name: "SmartScannerSDK",
            path: "1.0.0/SmartScannerSDK.xcframework"
        )
    ]
)
