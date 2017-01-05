using UnityEngine;
using UnityEngine.UI;
using System;
using System.Collections;
using Wikitude;
using System.Runtime.InteropServices;

/// <summary>
/// Handles forwarding the camera frame to the custom renderer.
/// </summary>
public class CustomRenderingController : CustomCameraController
{
	public CustomCameraRenderer Renderer;

	protected override void ResetBuffers(int width, int height, int bytesPerPixel) {
		base.ResetBuffers(width, height, bytesPerPixel);
		Renderer.CurrentFrame = _feed;
	}

	protected override void Cleanup() {
		base.Cleanup();
		if (Renderer) {
			Renderer.CurrentFrame = null;
		}
	}
}
