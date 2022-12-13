//
//  ScannerViewModelExample.swift
//  SmartScannerExample
//
//  Created by SAM Seamless Network on 12/8/22.
//

import Foundation
import Combine

#if targetEnvironment(simulator)
import SmartScannerSDKSimulator
#else
import SmartScannerSDK
#endif

final class ScannerViewModelExample: ObservableObject {
    private let scanner: Scan
    private var cancellables = Set<AnyCancellable>()

    init() {
        self.scanner = SmartScanner.getInstance().getScanInstance()
    }

    func setupScanner(token: String) {
        SmartScanner.getInstance().setup(token: token)
    }

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

    func observeScanProgress() {
        scanner
            .observeProgress()
            .receive(on: RunLoop.main)
            .sink { value in
                print("Progress: \(value)")
            }
            .store(in: &cancellables)
    }

    func observerScanDevices() {
        scanner
            .observeDevices()
            .receive(on: RunLoop.main)
            .sink(receiveCompletion: { error in
                print("The scanner encountered an error: \(error)")
            }, receiveValue: { devices in
                print("Detected devices: \(devices)")
            })
            .store(in: &cancellables)
    }

    func stopScan() {
        scanner.killScan()
    }

    private func handle401UnauthorizedErrorAndRescan() {
        setupScanner(token: refreshToken())
        startScan()
    }

    private func refreshToken() -> String {
        // Refresh the token and return a new valid one
    }
}

