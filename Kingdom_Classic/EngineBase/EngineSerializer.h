#pragma once

class UEngineFile;

class UEngineSerializer
{
	friend UEngineFile;

public:
	UEngineSerializer();
	~UEngineSerializer();

	UEngineSerializer(const UEngineSerializer& _Other) = delete;
	UEngineSerializer(UEngineSerializer&& _Other) noexcept = delete;
	UEngineSerializer& operator=(const UEngineSerializer& _Other) = delete;
	UEngineSerializer& operator=(UEngineSerializer&& _Other) noexcept = delete;

	void operator>>(int& _Data)
	{
		Read(&_Data, sizeof(int));
	}
	void operator>>(std::string& _Data)
	{
		int Size = 0;
		operator>>(Size);

		if (Size == 0)
		{
			return;
		}
		_Data.resize(Size);
		Read(&_Data[0], Size);
	}

	void operator<<(const int& _Data)
	{
		Write(&_Data, sizeof(int));
	}
	void operator<<(const bool& _Data)
	{
		Write(&_Data, sizeof(bool));
	}
	void operator<<(const std::string& _Data)
	{
		int Size = static_cast<int>(_Data.size());
		operator<<(Size);
		Write(_Data.c_str(), Size);
	}

	void Read(void* _Data, size_t _Size);
	void Write(const void* _Data, size_t _Size);
	void WriteText(const std::string& _Text);

	void BufferResize(int _Size);
	std::string ToString();

protected:

private:
	unsigned int ReadOffset = 0;
	unsigned int WriteOffset = 0;

	std::vector<char> Data;
};

class UEngineSerializeObject
{
public:
	virtual void Serialize(UEngineSerializer& _Ser) = 0;
	virtual void DeSerialize(UEngineSerializer& _Ser) = 0;
};