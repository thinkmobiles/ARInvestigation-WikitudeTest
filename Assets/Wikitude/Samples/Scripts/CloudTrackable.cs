using System;
using Wikitude;

public class CloudTrackable : ToggleTrackable
{
	public ContinuousTrackerController Controller;

	public override void OnEnterFieldOfVision(string targetName) {
		base.OnEnterFieldOfVision(targetName);

		if (Controller != null) {
			Controller.OnTargetFound();
		}
	}

	public override void OnExitFieldOfVision(string targetName) {
		base.OnExitFieldOfVision(targetName);

		if (Controller != null) {
			Controller.OnTargetLost();
		}
	}
}

