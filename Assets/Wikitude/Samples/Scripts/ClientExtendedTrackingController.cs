using UnityEngine;
using UnityEngine.UI;
using System.Collections;
using Wikitude;

public class ClientExtendedTrackingController : SampleController 
{
	public Text trackingQualityText;
	public Image trackingQualityBackground;

	public void OnTrackingQualityChanged(string targetName, ExtendedTrackingQuality newQuality) {
		if (targetName == null) {
			trackingQualityText.text = "No target";
			trackingQualityBackground.color = Color.red;
		} else {
			switch (newQuality) {
			case ExtendedTrackingQuality.Bad: 
				trackingQualityText.text = "Target: " + targetName + " Quality: Bad";
				trackingQualityBackground.color = Color.red;
				break;
			case ExtendedTrackingQuality.Average:
				trackingQualityText.text = "Target: " + targetName + " Quality: Average";
				trackingQualityBackground.color = Color.yellow;
				break;
			case ExtendedTrackingQuality.Good:
				trackingQualityText.text = "Target: " + targetName + " Quality: Good";
				trackingQualityBackground.color = Color.green;
				break;
			default:
				break;
			}
		}
	}

	public void OnExitFieldOfVision(string target) {
		trackingQualityText.text = "Target lost";
		trackingQualityBackground.color = Color.red;
	}
}
