Shader "Wikitude/ScanEffect"
{
	Properties
	{
		_MainTex ("Texture", 2D) = "white" {}
	}
	SubShader
	{
		// No culling or depth
		Cull Off ZWrite Off ZTest Always

		Pass
		{
			CGPROGRAM
			#pragma vertex vert
			#pragma fragment frag
			
			#include "UnityCG.cginc"

			struct appdata
			{
				float4 vertex : POSITION;
				float2 uv : TEXCOORD0;
			};

			struct v2f
			{
				fixed2 uv : TEXCOORD0;
				float4 vertex : SV_POSITION;
			};

			float _FlipU;
			float _FlipV;
			float _Rotate;

			float _Scale;
			float _Pan;

			v2f vert (appdata v)
			{
				v2f o;
				o.vertex = mul(UNITY_MATRIX_MVP, v.vertex);
				o.uv = v.uv;

				if (_FlipU)
				{
					o.uv.x = 1.0 - o.uv.x;
				}

				if (_FlipV) 
				{
					o.uv.y = 1.0f - o.uv.y;
				}

				if (_Rotate) 
				{
					o.uv.xy = o.uv.yx;
				}

				o.uv *= float2(1.0f, _Scale);
				o.uv += float2(0.0f, _Pan);

				return o;
			}
			
			sampler2D _MainTex;
			int _ResolutionX;
			int _ResolutionY;


			fixed RGB2Luminance(in fixed3 rgb)
			{
			    return 0.2126 * rgb.r + 0.7152 * rgb.g + 0.0722 * rgb.b;
			}

			fixed ComputeSobel(fixed c, fixed2 uv)
			{
				fixed2 pixelSize = 1.0 / fixed2(_ResolutionX, _ResolutionY);

			    fixed tl = RGB2Luminance(tex2D(_MainTex, uv - pixelSize).rgb);
			    fixed t = RGB2Luminance(tex2D(_MainTex, uv + fixed2(0.0, -pixelSize.y)).rgb);
			    fixed tr = RGB2Luminance(tex2D(_MainTex, uv + fixed2(pixelSize.x, -pixelSize.y)).rgb);

			    fixed cl = RGB2Luminance(tex2D(_MainTex, uv + fixed2(-pixelSize.x, 0.0)).rgb);
			    fixed cr = RGB2Luminance(tex2D(_MainTex, uv + fixed2(pixelSize.x, 0.0)).rgb);

			    fixed bl = RGB2Luminance(tex2D(_MainTex, uv + fixed2(-pixelSize.x, pixelSize.y)).rgb);
				fixed b = RGB2Luminance(tex2D(_MainTex, uv + fixed2(0.0, pixelSize.y)).rgb);
			    fixed br = RGB2Luminance(tex2D(_MainTex, uv + pixelSize).rgb);

			    fixed sobelX = tl * -1.0 + tr * 1.0 + cl * -2.0 + cr * 2.0 + bl * -1.0 + br * 1.0;
			    fixed sobelY = tl * -1.0 + t * -2.0 + tr * -1.0 + bl * 1.0 + b * 2.0 + br * 1.0;

			    return sqrt(sobelX * sobelX + sobelY * sobelY);
			}

			fixed4 frag (v2f i) : SV_Target
			{
			    fixed4 textureColor = tex2D(_MainTex, i.uv);
				fixed c = RGB2Luminance(textureColor.rgb);

		    	fixed sobel = ComputeSobel(c, i.uv);

		    	fixed scanlineY = _SinTime.w * 0.5 + 0.5;
    			
    			fixed scanWindowHeight = 0.25;
    			fixed distanceToScanline = clamp(0.0, scanWindowHeight, abs(scanlineY - i.uv.y)) / scanWindowHeight;
                return fixed4(lerp(lerp(c, fixed3(1.0, 0.549, 0.0392), step(0.15, sobel)), textureColor.rgb, smoothstep(0.3, 0.7, distanceToScanline)), 1.0);
			}
			ENDCG
		}
	}
}
