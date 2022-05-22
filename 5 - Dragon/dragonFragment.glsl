#version 300 es

out highp vec4 FragColor;

uniform highp vec3 lightPosition, cameraPosition, color;
uniform highp float ambientLight, specularStrength, shininess;
in highp vec3 Normal, FragPos;

highp vec3 light();

void main()
{
    FragColor = vec4(color * light(), 1.0f);
}

highp vec3 light()
{
    highp vec3 lightDirection = normalize(lightPosition - FragPos);
    highp vec3 viewDirection = normalize(cameraPosition - FragPos);

    highp float specular = pow(max(dot(viewDirection, reflect(-lightDirection, Normal)), 0.0f), shininess);
	highp float lightResultant = ambientLight + max(dot(Normal, lightDirection), 0.0f);

	return vec3(lightResultant) + (specularStrength * vec3(specular));
}
