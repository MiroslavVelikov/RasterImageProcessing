template <typename T>
Image<T>::Image(const std::string& name, size_t width, size_t height, const std::vector<std::vector<T>>& pixels) {
	try {
		this->name = name;
		setWidth(width);
		setHeight(height);
		setPixels(pixels);
	}
	catch (const std::exception& e) {
		std::cout << e.what();
		this->width = this->height = 0;
		this->pixels.clear();
	}
}

template <typename T>
inline void Image<T>::setWidth(size_t value) {
	if (value > MAX_SIZE)
		throw std::invalid_argument("Invalid image width!\n");

	width = value;
}
// invalid_argument

template <typename T>
inline void Image<T>::setHeight(size_t value) {
	if (value > MAX_SIZE)
		throw std::invalid_argument("Invalid image height!\n");

	height = value;
}
// invalid_argument

template <typename T>
inline void Image<T>::setPixels(const std::vector<std::vector<T>>& value) {
	if (width != value.size() || height != value[0].size())
		throw std::invalid_argument("Invalid image size!\n");

	pixels = value;
}
// invalid_argument

template <typename T>
inline void Image<T>::negative() {
	flipTop();
	flipLeft();
}

template <typename T>
inline void Image<T>::rotateLeft() {
	std::vector<std::vector<T>> rotated(height, std::vector<T>(width));

	for (size_t i = 0; i < height; i++) {
		for (size_t j = 0; j < width; j++) {
			rotated[i][width - j - 1] = pixels[j][i];
		}
	}

	pixels = rotated;
	width = height;
	height = pixels[0].size();
}

template <typename T>
inline void Image<T>::rotateRight() {
	std::vector<std::vector<T>> rotated(height, std::vector<T>(width));

	for (size_t i = 0; i < height; i++) {
		for (size_t j = 0; j < width; j++) {
			rotated[height - i - 1][j] = pixels[j][i];
		}
	}

	pixels = rotated;
	width = height;
	height = pixels[0].size();
}

template <typename T>
inline void Image<T>::flipTop() {
	for (size_t i = 0; i < height / 2; i++) {
		for (size_t j = 0; j < width; j++) {
			T temp = pixels[j][i];
			pixels[j][i] = pixels[j][height - i - 1];
			pixels[j][height - i - 1] = temp;
			//std::swap(pixels[j][i], pixels[j][height - i - 1]);
		}
	}
}

template <typename T>
inline void Image<T>::flipLeft() {
	for (size_t i = 0; i < width / 2; i++) {
		std::swap(pixels[i], pixels[width - i - 1]);
	}
}

template <typename T>
inline void Image<T>::crop(size_t x1, size_t y1, size_t x2, size_t y2) {
	if (x1 >= x2 || x1 >= width || y1 >= y2 || y1 >= height) {
		height = width = 0;
		pixels.clear();
		return;
	}

	if (x2 >= width)
		x2 = width - 1;
	if (y2 >= height)
		y2 = height - 1;

	std::vector<std::vector<T>> croped(x2 - x1 + 1, std::vector<T>(y2 - y1 + 1));

	for (size_t i = y1; i <= y2; i++) {
		for (size_t j = x1; j <= x2; j++) {
			croped[j - y1][i - x1] = pixels[j][i];
		}
	}	

	pixels = croped;
	width = pixels.size();
	height = pixels[0].size();
}

template <typename T>
inline void Image<T>::print() const {
	for (size_t i = 0; i < height; i++) {
		for (size_t j = 0; j < width; j++) {
			std::cout << pixels[j][i] << ' ';
		}
		std::cout << '\n';
	}
}

template <typename T>
void Image<T>::enlargeHeight(size_t newHeight, size_t blackValue) {
	std::vector<std::vector<T>> temp(width, std::vector<T>(newHeight, blackValue));

	for (size_t i = 0; i < height; i++) {
		for (size_t j = 0; j < width; j++) {
			temp[j][i] = pixels[j][i];
		}
	}

	pixels = temp;
	height = newHeight;
}

template <typename T>
void Image<T>::enlargeWidth(size_t newWidth, size_t blackValue) {
	std::vector<std::vector<T>> temp(newWidth, std::vector<T>(height, blackValue));

	for (size_t i = 0; i < height; i++) {
		for (size_t j = 0; j < width; j++) {
			temp[j][i] = pixels[j][i];
		}
	}

	pixels = temp;
	width = newWidth;
}