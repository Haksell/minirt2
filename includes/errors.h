#ifndef ERRORS_H
# define ERRORS_H

# define USAGE_MANDATORY "Usage: ./miniRT *.rt"
# define USAGE_BONUS "Usage: ./miniRTbonus *.rtb"

# define SPACY_LINE "Line contains only spaces and tabulations"
# define OPEN_ERROR "File cannot be opened"
# define MALLOC_ERROR "Impossible to allocate heap memory"
# define READ_ERROR "Error while reading the file"
# define INVALID_IDENTIFIER "Invalid identifier"

# define DOUBLE_AMBIENT "Too many ambient lights"
# define DOUBLE_CAMERA "Too many cameras"
# define DOUBLE_LIGHT "Too many lights"
# define ERROR_AMBIENT "Error parsing ambient light"
# define ERROR_CAMERA "Error parsing camera"
# define ERROR_LIGHT "Error parsing light"
# define NO_CAMERA "There is no camera"
# define NO_LIGHT "There is no light"
# define FOV_ERROR "Field of view is invalid"

# define ERROR_CYLINDER "Error parsing cylinder"
# define ERROR_PLANE "Error parsing plane"
# define ERROR_SPHERE "Error parsing sphere"

# define ERROR_MLX "Failed to initialize mlx"
# define ERROR_WINDOW "Failed to initialize window"
# define ERROR_IMAGE "Failed to initialize image"
# define ERROR_ADDR "Failed to initialize addr"

#endif
