using UnityEngine;
#if UNITY_5_3_OR_NEWER
using UnityEngine.SceneManagement;
#endif
using UnityEngine.UI;
using System.Collections;

public class MenuController : MonoBehaviour
{
	public void OnSampleButtonClicked(Button sender) {
		#if UNITY_5_3_OR_NEWER
		SceneManager.LoadScene(sender.name);
		#else
		Application.LoadLevel(sender.name);
		#endif
	}


	void Update() {
		// Also handles the back button on Android
		if (Input.GetKeyDown(KeyCode.Escape)) { 
			Application.Quit();
		}
	}
}