/*
 * User class
 *
 * Copyright 2014 I.Karbachinsky <igorkarbachinsky@mail.ru>
 */


#ifndef NEWYEAR_ROULETTE_LIB_USER_HPP_
#define NEWYEAR_ROULETTE_LIB_USER_HPP_

#include <memory>
#include <vector>

namespace roulette {

class User;

typedef std::vector<std::shared_ptr<User> > user_pointers_list_t;

class User {
public:
    User(const std::string &name, const std::string &email) :
            name_(name),
            email_(email),
            is_busy_(false)
    {}

    /**
    * Checks whether user is already has user to be gifted
    */
    const bool IsBusy() const {
        return is_busy_;
    }

    /**
    * Set user busy (this user is already gifted by someone)
    */
    const bool SetBusy() const {
        is_busy_ = true;
    }

    /**
    * Checks if input user can be gifted by this user
    */
    bool CanBeGiftedBy(const std::shared_ptr<const User> user_ptr) const {
        if (IsBusy())
            return false;
        if (*user_ptr == *this)
            return false;
        if (loved_user_ != nullptr && user_ptr == loved_user_)
            return false;
        return true;
    }

    /**
    * Updates user to be gifted
    */
    void SetUserToBeGifted(const std::shared_ptr<const User> user_ptr) {
        user_to_be_gifted_ = user_ptr;
        user_ptr->SetBusy();
    }

    /**
    * Get user which will be gifted the gift by current user
    */
    const std::shared_ptr<const User> GetUserToBeGifted() const {
        auto user_ptr = user_to_be_gifted_.lock();
        return user_ptr;
    }

    /**
    * Set love relation for user
    */
    void SetLoved(const std::shared_ptr<const User> user_ptr) {
        loved_user_ = user_ptr;
    }

    /**
    * Get love realtion user
    */
    const std::shared_ptr<const User> GetLoved() const {
        return loved_user_;
    }

    /**
    * Get user's name
    */
    const std::string GetName() const {
        return name_;
    }

    /**
    * Get user's email
    */
    const std::string GetEmail() const {
        return email_;
    }

    bool operator==(const User &other) const {
        return other.email_ == email_;
    }

private:
    const std::string name_;
    const std::string email_;
    mutable bool is_busy_;
    std::weak_ptr<const User> user_to_be_gifted_;
    std::shared_ptr<const User> loved_user_;
};

} // namespace roulette

#endif // NEWYEAR_ROULETTE_LIB_USER_HPP_