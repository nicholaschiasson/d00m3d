#ifndef OGRE_APP_EXCEPTION_H
#define OGRE_APP_EXCEPTION_H

/* Our exception type */
class OgreAppException: public std::exception
{
	private:
		std::string message_;
	public:
		OgreAppException(std::string message) : message_(message) {};
		virtual const char* what() const throw() { return message_.c_str(); };
};

#endif // OGRE_APP_EXCEPTION_H