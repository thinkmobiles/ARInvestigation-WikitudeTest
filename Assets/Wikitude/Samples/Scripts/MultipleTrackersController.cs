using UnityEngine;
using System.Collections;
using Wikitude;

public class MultipleTrackersController : SampleController 
{
	public ClientTracker CarTracker;
	public ClientTracker MagazineTracker;

	public GameObject CarInstructions;
	public GameObject MagazineInstructions;

	private bool _waitingForTrackerToLoad = false;

	public void OnTrackCar() {
		if (!CarTracker.enabled && !_waitingForTrackerToLoad) {
			_waitingForTrackerToLoad = true;

			MagazineInstructions.SetActive(false);
			CarInstructions.SetActive(true);

			CarTracker.enabled = true;
		}
	}

	public void OnTrackMagazine() {
		if (!MagazineTracker.enabled && !_waitingForTrackerToLoad) {
			_waitingForTrackerToLoad = true;
			MagazineInstructions.SetActive(true);

			CarInstructions.SetActive(false);

			MagazineTracker.enabled = true;
		}
	}

	public void OnTrackerFinishedLoading(string message) {
		_waitingForTrackerToLoad = false;
	}
}
